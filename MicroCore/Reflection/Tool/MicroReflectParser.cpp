/**
 *
 *  __  __ _             ___
 * |  \/  (_)__ _ _ ___ / __|___ _ _ ___
 * | |\/| | / _| '_/ _ \ (__/ _ \ '_/ -_)
 * |_|  |_|_\__|_| \___/\___\___/_| \___|
 *
 * MIT License
 *
 * Copyright (c) 2024 Alves Quentin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroReflectParser::MicroReflectParser( )
	: m_extensions{ },
	m_arguments{ },
	m_directories{ },
	m_emitters{ },
	m_options{ }
{
	AddExtensions( { ".h", ".hpp" } );
	AddArguments( { "-x", "c++", "-std=c++20", "-D__MICRO_REFLECT__" } );
	AddOptions( { 
		CXTranslationUnit_IncludeAttributedTypes,
		CXTranslationUnit_VisitImplicitAttributes 
	} );
}

void MicroReflectParser::AddExtension( const std::string& extension ) {
	if ( !extension.empty( ) )
		m_extensions.emplace_back( std::move( extension ) );
}

void MicroReflectParser::AddExtensions( std::initializer_list<std::string> extensions ) {
	for ( const auto& extension : extensions )
		AddExtension( std::move( extension ) );
}

void MicroReflectParser::AddOption( const uint32_t option ) {
	AddOptions( { option } );
}

void MicroReflectParser::AddOptions( std::initializer_list<uint32_t> options ) {
	for ( const auto option : options )
		m_options |= option;
}

void MicroReflectParser::AddArgument( const std::string& argument ) {
	if ( !argument.empty( ) )
		m_arguments.emplace_back( std::move( argument ) );
}

void MicroReflectParser::AddArguments( std::initializer_list<std::string> arguments ) {
	for ( const auto& argument : arguments )
		AddArgument( std::move( argument ) );
}

void MicroReflectParser::AddDirectory( const std::string& directory ) {
	if ( !directory.empty( ) )
		m_directories.emplace_back( std::move( directory ) );
}

void MicroReflectParser::AddDirectories( std::initializer_list<std::string> directories ) {
	for ( const auto& directory : directories )
		AddDirectory( directory );
}

void MicroReflectParser::ParseArguments( 
	const int32_t argument_count, 
	const char** argument_values
) {
	auto arg_count = argument_count;

	while ( arg_count-- > 0 ) {
		const auto* argument = argument_values[ arg_count ];
		const auto value	 = std::string{ argument + 2 };

		if ( argument[ 0 ] != '-' || strlen( argument ) < 3 )
			continue;

		switch ( argument[ 1 ] ) {
			case 'A' : AddArgument( value );  break;
			case 'D' : AddDirectory( value ); break;
			case 'E' : AddExtension( value ); break;

			default : break;
		}
	}
}

void MicroReflectParser::Run( const std::filesystem::path& source_path ) {
	if ( !std::filesystem::is_directory( source_path ) ) {
		auto declaration = MicroReflectSourceDeclaration{ source_path };
		auto entry_ext   = source_path.extension( );
		auto extension   = entry_ext.string( );

		if ( CanParse( extension ) && ProcessClang( source_path, declaration ) ) {
			for ( const auto& emitter : m_emitters )
				emitter->Run( declaration );
		}
	} else {
		for ( const auto& entry : std::filesystem::directory_iterator{ source_path } ) {
			auto entry_path = entry.path( );
			
			Run( entry_path );
		}
	}
}

void MicroReflectParser::Run(
	const int32_t argument_count,
	const char** argument_values
) {
	ParseArguments( argument_count, argument_values );

	for ( const auto& directory : m_directories )
		Run( { directory } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroReflectParser::ProcessClang(
	const std::filesystem::path& source_path,
	MicroReflectSourceDeclaration& declaration
) {
	auto clang_index = clang_createIndex( 0, 0 );
	auto path_string = source_path.string( );
	auto arguments   = GetArguments( );
	auto* arg_values = arguments.data( );
	auto arg_count   = (uint32_t)arguments.size( );
	auto result		 = false;
	auto* path		 = path_string.c_str( );
	
	if ( auto clang_unit = clang_parseTranslationUnit( clang_index, path, arg_values, arg_count, NULL, 0, m_options ) ) {
		auto root = clang_getTranslationUnitCursor( clang_unit );

		clang_visitChildren( root, ClangVisitor, (CXClientData)&declaration );
		clang_disposeTranslationUnit( clang_unit );

		result = declaration.GetIsValid( );
	}

	clang_disposeIndex( clang_index );

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
CXChildVisitResult MicroReflectParser::ClangVisitor(
	CXCursor cursor,
	CXCursor parent,
	CXClientData user_data
) {
	auto* declaration = reinterpret_cast<MicroReflectSourceDeclaration*>( user_data );

	const CXCursorKind parent_kind = clang_getCursorKind( parent );
	const CXCursorKind cursor_kind = clang_getCursorKind( cursor );
	const CXType cursor_type = clang_getCursorType( cursor );
	const bool is_attr = clang_isAttribute( cursor_kind ) != 0;
	const bool has_attr = clang_Cursor_hasAttrs( cursor );

	auto display_name = ClangGetString( clang_getCursorDisplayName, cursor );
	auto spelling = ClangGetString( clang_getCursorSpelling, cursor );
	auto parent_spelling = ClangGetString( clang_getCursorKindSpelling, parent_kind );
	auto kind_spelling = ClangGetString( clang_getCursorKindSpelling, cursor_kind );
	auto type_spelling = ClangGetString( clang_getTypeSpelling, cursor_type );

	auto format_message = std::format(
		"[{}] {} <{}> '{}' [{}]", 
		parent_spelling, 
		kind_spelling, 
		type_spelling, 
		spelling, 
		is_attr ? "ATTRIB" : ( has_attr ? "HAS_ATTR" : "" )
	);
	printf( "%s\n", format_message.c_str( ) );

	clang_visitChildren( cursor, ClangVisitor, user_data );

	return CXChildVisit_Continue;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroReflectParser::CanParse( const std::filesystem::path& extension ) const {
	auto first_element = m_extensions.begin( );
	auto last_element  = m_extensions.end( );
	auto result		   = std::find_if(
		first_element,
		last_element,
		[ extension ]( const std::string& value ) {
			return extension == value;
		}
	);

	return result != last_element;
}

std::vector<const char*> MicroReflectParser::GetArguments( ) const {
	auto argument_id = m_arguments.size( );
	auto arguments   = std::vector<const char*>{ argument_id };

	while ( argument_id-- > 0 )
		arguments[ argument_id ] = m_arguments[ argument_id ].c_str( );

	return arguments;
};

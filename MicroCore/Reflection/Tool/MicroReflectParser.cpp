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
{ }

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

void MicroReflectParser::InitializeGeneric( ) {
	AddExtensions( { ".h", ".hpp" } );
	AddArguments( { "-x", "c++", "-std=c++20", "-D__MICRO_REFLECT__" } );
	AddOptions( {
		CXTranslationUnit_IncludeAttributedTypes,
		CXTranslationUnit_VisitImplicitAttributes
	} );
}

void MicroReflectParser::RegisterGeneric( ) {
	Register<MicroReflectGenerator>( );
	Register<MicroYamlGenerator>( );
}

void MicroReflectParser::ParseArguments( 
	const int32_t argument_count, 
	const char** argument_values
) {
	auto arg_count = argument_count;

	while ( arg_count-- > 0 ) {
		const auto* argument = argument_values[ arg_count ];
		const auto value	 = std::string{ argument + 2 };

		if ( argument[ 0 ] != '-' || value.size( ) == 0 )
			continue;

		switch ( argument[ 1 ] ) {
			case 'A' : AddArgument( value );  break;
			case 'D' : AddDirectory( value ); break;
			case 'E' : AddExtension( value ); break;

			default : break;
		}
	}
}

void MicroReflectParser::Run( const std::string& name, const std::string& source ) {
	const auto arguments = GetArguments( );
	auto unsaved_file	 = CXUnsavedFile{ };
	auto context		 = MicroReflectParsingContext{ "unsaved.txt" };
	
	unsaved_file.Filename = "unsaved.txt";
	unsaved_file.Contents = source.c_str( );
	unsaved_file.Length   = (uint32_t)source.size( );

	if ( ProcessClangSource( arguments, unsaved_file, context ) )
		RunEmitters( context );
}

void MicroReflectParser::Run( const std::filesystem::path& source_path ) {
	const auto arguments = GetArguments( );

	RunParser( arguments, source_path );
}

void MicroReflectParser::Run(
	const int32_t argument_count,
	micro_string* argument_values
) {
	ParseArguments( argument_count, argument_values );

	const auto arguments = GetArguments( );

	for ( const auto& directory : m_directories )
		RunParser( arguments, { directory } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroReflectParser::RunParser(
	const std::vector<micro_string>& arguments,
	const std::filesystem::path& source_path
) {
	micro_assert( m_extensions.size( ) > 0, "You can't run reflection parser without supported extensions filled." );
	micro_assert( m_arguments.size( ) > 0, "You can't run reflection parser without at least one argument for language specification." );

	if ( !std::filesystem::is_directory( source_path ) ) {
		auto entry_ext = source_path.extension( );
		auto extension = entry_ext.string( );
		auto context   = MicroReflectParsingContext{ std::move( source_path ) };

		if ( CanParse( extension ) && ProcessClang( arguments, context ) )
			RunEmitters( context );
	} else {
		for ( const auto& entry : std::filesystem::directory_iterator{ source_path } ) {
			const auto entry_path = entry.path( );

			Run( entry_path );
		}
	}
}

bool MicroReflectParser::ProcessClang( 
	const std::vector<micro_string>& arguments, 
	MicroReflectParsingContext& context 
) {
	const auto* path = context.GetPath( );
	const auto* argv = arguments.data( );
	const auto argc  = (uint32_t)arguments.size( );
	auto clang_index = clang_createIndex( 0, 0 );
	auto result		 = false;
	
	if ( auto clang_unit = clang_parseTranslationUnit( clang_index, path, argv, argc, NULL, 0, m_options ) ) {
		auto* user_data  = micro_ptr_as( context, CXClientData );
		auto root		 = clang_getTranslationUnitCursor( clang_unit );

		clang_visitChildren( root, ClangVisitor, user_data );
		clang_disposeTranslationUnit( clang_unit );

		result = context.GetIsValid( );
	}

	clang_disposeIndex( clang_index );

	return result;
}

bool MicroReflectParser::ProcessClangSource(
	const std::vector<micro_string>& arguments,
	CXUnsavedFile& save,
	MicroReflectParsingContext& context
) {
	const auto* argv = arguments.data( );
	const auto argc  = (uint32_t)arguments.size( );
	auto clang_index = clang_createIndex( 0, 0 );
	auto result		 = false;

	if ( auto clang_unit = clang_parseTranslationUnit( clang_index, save.Filename, argv, argc, micro_ptr( save ), 1, m_options ) ) {
		auto* user_data = micro_ptr_as( context, CXClientData );
		auto root		= clang_getTranslationUnitCursor( clang_unit );

		clang_visitChildren( root, ClangVisitor, user_data );
		clang_disposeTranslationUnit( clang_unit );

		result = context.GetIsValid( );
	}

	clang_disposeIndex( clang_index );

	return result;
}

void MicroReflectParser::RunEmitters( MicroReflectParsingContext& context ) {
	for ( auto& emitter : m_emitters )
		emitter->PreRun( context );

	for ( const auto& emitter : m_emitters ) {
		if ( !context.GetCanEmit( ) )
			break;
		
		emitter->Run( context );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
CXChildVisitResult MicroReflectParser::ClangVisitor(
	CXCursor cursor,
	CXCursor parent,
	CXClientData user_data
) {
	micro_assert( user_data != nullptr, "You can't visit libclang Ast without user_data for storing parsed information." );

	auto parent_kind = clang_getCursorKind( parent );
	auto cursor_kind = clang_getCursorKind( cursor );
	auto* context	 = micro_cast( user_data, MicroReflectParsingContext* );
	auto name		 = ClangGetString( clang_getCursorSpelling, cursor );

	if ( parent_kind == CXCursor_TranslationUnit )
		context->CreateDeclaration( cursor_kind, std::move( name ) );
	else if ( cursor_kind == CXCursor_AnnotateAttr ) 
		context->ParseAnnotation( std::move( name ) );
	else if ( cursor_kind == CXCursor_CXXAccessSpecifier ) {
		auto accessor = clang_getCXXAccessSpecifier( cursor );

		context->ParseAccessor( accessor );
	} else {
		auto cursor_type = clang_getCursorType( cursor );
		auto type		 = ClangGetString( clang_getTypeSpelling, cursor_type );

		if ( cursor_kind == CXCursor_EnumConstantDecl )
			context->CreateEnumConstant( std::move( name ) );
		else if ( cursor_kind == CXCursor_FieldDecl ) 
			context->CreateField( std::move( type ), std::move( name ) );
		else if ( GetIsFunction( cursor_kind ) ) 
			context->CreateFunction( std::move( type ), std::move( name ) );
		else if ( cursor_kind == CXCursor_ParmDecl )
			context->CreateParameter( std::move( type ), std::move( name ) );
	}

	return CXChildVisit_Recurse;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED GET ===
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

std::vector<micro_string> MicroReflectParser::GetArguments( ) const {
	auto argument_id = m_arguments.size( );
	auto arguments   = std::vector<micro_string>{ argument_id };

	while ( argument_id-- > 0 )
		arguments[ argument_id ] = m_arguments[ argument_id ].c_str( );

	return std::move( arguments );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED STATIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroReflectParser::GetIsFunction( const CXCursorKind cursor_kind ) {
	return  cursor_kind == CXCursor_FunctionDecl ||
			cursor_kind == CXCursor_CXXMethod	 ||
			cursor_kind == CXCursor_Constructor  ||
			cursor_kind == CXCursor_Destructor;
}

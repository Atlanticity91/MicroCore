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
MicroReflectParsingContext::MicroReflectParsingContext( 
	const std::filesystem::path&& source_path
)
	: m_source{ std::move( source_path ) },
	m_type{ MRP_TYPE_ROOT },
	m_accessor{ MicroReflectAccessor::Public }
{ 
	m_path = m_source.Source.string( );
	m_node = micro_ptr_as( m_source, MicroReflectParsingNode );
}

void MicroReflectParsingContext::CreateDeclaration(
	const CXCursorKind cursor_kind,
	std::string&& name
) {
	m_accessor = MicroReflectAccessor::Public;
	
	switch ( cursor_kind ) {
		case CXCursor_Namespace  : CreateNamespace( std::move( name ) ); break;
		case CXCursor_EnumDecl   : CreateEnum( std::move( name ) );		 break;
		case CXCursor_StructDecl : CreateClass( std::move( name ) );	 break;
		case CXCursor_ClassDecl  : CreateClass( std::move( name ) );	 break;

		default : 
			m_type = MRP_TYPE_ROOT;
			m_node = micro_ptr_as( m_source, MicroReflectParsingNode );

			break;
	}
}

void MicroReflectParsingContext::ParseAnnotation( std::string&& annotation ) {
	auto* declaration = (MicroReflectDeclaration*)m_node;

	declaration->Annotations;
}

void MicroReflectParsingContext::ParseAccessor( const CX_CXXAccessSpecifier accessor ) {
	switch ( accessor ) {
		case CX_CXXPublic	 : m_accessor = MicroReflectAccessor::Public;    break;
		case CX_CXXProtected : m_accessor = MicroReflectAccessor::Protected; break;
		case CX_CXXPrivate	 : m_accessor = MicroReflectAccessor::Private;   break;

		default : break;
	}
}

void MicroReflectParsingContext::CreateEnumConstant( std::string&& name ) {
	if ( auto* declaration = GetDeclaration<MRP_TYPE_ENUM, MicroReflectEnumDeclaration>( ) )
		declaration->Values.emplace_back( std::move( name ) );
}

void MicroReflectParsingContext::CreateField( std::string&& type, std::string&& name ) {
	if ( auto* declaration = GetDeclaration<MRP_TYPE_CLASS, MicroReflectClassDeclaration>( ) )
		declaration->Fields.emplace_back( std::move( name ), std::move( type ), m_accessor );
}

void MicroReflectParsingContext::CreateFunction( std::string&& type, std::string&& name ) {
	auto* function = micro_cast( nullptr, MicroReflectFunctionDeclaration* );

	if ( auto* declaration = GetDeclaration<MRP_TYPE_NAMESPACE, MicroReflectNamespaceDeclaration>( ) ) {
		declaration->Functions.emplace_back( std::move( name ), std::move( type ) );

		function = micro_ptr( declaration->Functions.back( ) );
	} else if ( auto* declaration = GetDeclaration<MRP_TYPE_CLASS, MicroReflectClassDeclaration>( ) ) {
		declaration->Functions.emplace_back( std::move( name ), std::move( type ), m_accessor );
		
		function = micro_ptr( declaration->Functions.back( ) );
	}

	m_type = MRP_TYPE_FUNCTION;
	m_node = micro_cast( function, MicroReflectParsingNode );
}

void MicroReflectParsingContext::CreateParameter( std::string&& type, std::string&& name ) {
	if ( auto* declaration = GetDeclaration<MRP_TYPE_FUNCTION, MicroReflectFunctionDeclaration>( ) )
		declaration->Parameters.emplace_back( std::move( name ), std::move( type ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroReflectParsingContext::CreateNamespace( std::string&& name ) {
	m_source.Namespaces.emplace_back( std::move( name ) );

	m_type = MRP_TYPE_NAMESPACE;
	m_node = micro_ptr( m_source.Namespaces.back( ) );
}

void MicroReflectParsingContext::CreateEnum( std::string&& name ) {
	auto* declaration = GetRoot( );

	declaration->Enumerations.emplace_back( std::move( name ) );

	m_type = MRP_TYPE_ENUM;
	m_node = micro_ptr( declaration->Enumerations.back( ) );
}

void MicroReflectParsingContext::CreateClass( std::string&& name ) {
	auto* declaration = GetRoot( );

	declaration->Classes.emplace_back( std::move( name ) );

	m_type = MRP_TYPE_CLASS;
	m_node = micro_ptr( declaration->Classes.back( ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
micro_string MicroReflectParsingContext::GetPath( ) const {
	return m_path.c_str( );
}

bool MicroReflectParsingContext::GetIsValid( ) const {
	return m_source.GetIsValid( );
}

bool MicroReflectParsingContext::GetCanEmit( ) const {
	return true;
}

MicroReflectNamespaceDeclaration* MicroReflectParsingContext::GetRoot( ) {
	auto* result = micro_cast( m_node, MicroReflectNamespaceDeclaration* );

	if ( m_type != MRP_TYPE_NAMESPACE )
		result = micro_ptr_as( m_source, MicroReflectNamespaceDeclaration* );

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroReflectParsingContext::operator MicroReflectSourceDeclaration& ( ) {
	return m_source;
}

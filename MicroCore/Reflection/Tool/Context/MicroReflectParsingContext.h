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

#pragma once 

#include "MicroReflectParsingTypes.h"

extern "C" {
	#include <clang-c/Index.h>
};

typedef void* MicroReflectParsingNode;

/**
 * MicroReflectParsingContext class final
 * @note : Defined reflection system parsing context.
 **/
micro_class MicroReflectParsingContext final {

private:
	MicroReflectSourceDeclaration m_source;
	MicroReflectParsingTypes m_type;
	MicroReflectParsingNode m_node;
	MicroReflectAccessor m_accessor;
	std::string m_path;

public:
	/**
	 * Constructor
	 * @param source_path : Query source file path.
	 **/
	MicroReflectParsingContext( const std::filesystem::path&& source_path );

	/**
	 * CreateDeclaration method
	 * @note : Create declaration from name and clang cursor kind.
	 * @param cursor_kind : Query clang cursor kind.
	 * @param name : Query name.
	 **/
	void CreateDeclaration( 
		const CXCursorKind cursor_kind,
		std::string&& name 
	);

	/**
	 * ParseAnnotation method
	 * @note : Parse annotation to declaration annotation vector.
	 * @param annotation : Query annotation string to parse.
	 **/
	void ParseAnnotation( std::string&& annotation );

	/**
	 * ParseAccessor method
	 * @note : Parse clang accessor to MicroReflectAccessor.
	 * @param accessor : Query clang accessor value.
	 **/
	void ParseAccessor( const CX_CXXAccessSpecifier accessor );

	/**
	 * CreateEnumConstant method
	 * @note : Create enum constant.
	 * @param name : Query enum constant name.
	 **/
	void CreateEnumConstant( std::string&& name );

	/**
	 * CreateField method
	 * @note : Create MicroReflectClass field.
	 * @param type : Query field type.
	 * @param name : Query field name.
	 **/
	void CreateField( std::string&& type, std::string&& name );

	/**
	 * CreateFunction method
	 * @note : Create function.
	 * @param type : Query function return type.
	 * @param name : Query function name.
	 **/
	void CreateFunction( std::string&& type, std::string&& name );

	/**
	 * CreateParameter method
	 * @note : Create function or template parameter.
	 * @param type : Query parameter type.
	 * @param name : Query parameter name.
	 **/
	void CreateParameter( std::string&& type, std::string&& name );

private:
	/**
	 * CreateNamespace method
	 * @note : Create namespace.
	 * @param name : Query namespace name.
	 **/
	void CreateNamespace( std::string&& name );

	/**
	 * CreateEnum method
	 * @note : Create enum.
	 * @param name : Query enum name.
	 **/
	void CreateEnum( std::string&& name );

	/**
	 * CreateClass method
	 * @note : Create class.
	 * @param name : Query class name.
	 **/
	void CreateClass( std::string&& name );

public:
	/**
	 * GetPath const function
	 * @note : Get source path as C string.
	 * @return : Return source path as C string.
	 **/
	micro_string GetPath( ) const;

	/**
	 * GetIsValid const function
	 * @note : Get if context is valid after clang phase.
	 * @return : Return true when is valid.
	 **/
	bool GetIsValid( ) const;

	/**
	 * GetCanEmit const function
	 * @note : Get if context can be used for emittion.
	 * @return : Return true when context can be use by emitters.
	 **/
	bool GetCanEmit( ) const;

private:
	/**
	 * GetRoot function
	 * @note : Get root node.
	 * @return : Return root node.
	 **/
	MicroReflectNamespaceDeclaration* GetRoot( );

private:
	/**
	 * GetDeclaration template function
	 * @note : Get node casted as DeclarationType when node type match Type.
	 * @template Type : Query node type.
	 * @template DeclarationType : Query node cast type.
	 * @return : Return node casted as DeclarationType or nullptr.
	 **/
	template<MicroReflectParsingTypes Type, typename DeclarationType>
	DeclarationType* GetDeclaration( ) {
		return ( m_type == Type ) ? (DeclarationType*)m_node : nullptr;
	};

public:
	/**
	 * Cast operator
	 * @note : Replace getter by casting to source declaration.
	 * @return : Cast context to it's source declaration.
	 **/
	operator MicroReflectSourceDeclaration& ( );

};

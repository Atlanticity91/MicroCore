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

#include "MicroReflectGenerator.h"

extern "C" {
	#include <clang-c/Index.h>
};

class MicroReflectParser {

private:
	std::vector<std::string> m_extensions;
	std::vector<std::string> m_arguments;
	std::vector<std::string> m_directories;
	std::vector<std::unique_ptr<MicroReflectEmitter>> m_emitters;
	uint32_t m_options;

public:
	/**
	 * Constructor 
	 **/
	MicroReflectParser( );

	/**
	 * Destructor
	 **/
	virtual ~MicroReflectParser( ) = default;

	/**
	 * AddExtension method
	 * @note : Add extension to the extension list.
	 * @param extension : Query extension.
	 **/
	void AddExtension( const std::string& extension );

	/**
	 * AddExtensions method
	 * @note : Add extension list to the extension list.
	 * @param extensions : Query extension list.
	 **/
	void AddExtensions( std::initializer_list<std::string> extensions );

	/**
	 * AddOption method
	 * @note : Add option flag to current options.
	 * @param option : Query option flag.
	 **/
	void AddOption( const uint32_t option );

	/**
	 * AddOptions method
	 * @note : Add option flags to current options.
	 * @param option : Query option flags.
	 **/
	void AddOptions( std::initializer_list<uint32_t> options );

	/**
	 * AddArgument method
	 * @note : Add argument to current argument list.
	 * @param argument : Query argument.
	 **/
	void AddArgument( const std::string& argument );

	/**
	 * AddArguments method
	 * @note : Add argument list to current argument list.
	 * @param argument : Query argument list.
	 **/
	void AddArguments( std::initializer_list<std::string> arguments );

	/**
	 * AddDirectory method
	 * @note : Add directory to directory list.
	 * @param directory : Query directory.
	 **/
	void AddDirectory( const std::string& directory );

	/**
	 * AddDirectories method
	 * @note : Add directory list to directory list.
	 * @param directories : Query directory list.
	 **/
	void AddDirectories( std::initializer_list<std::string> directories );

	/**
	 * AddArguments method
	 * @note : Parse command lines arguments.
	 * @param argument_count : Command lines arguments count.
	 * @param argument_values : Command lines argument values.
	 **/
	void ParseArguments( 
		const int32_t argument_count,
		const char** argument_values 
	);

	/**
	 * Run method
	 * @note : Run parser on specific file or directory.
	 * @param source_path : Query source path.
	 **/
	void Run( const std::filesystem::path& source_path );

	/**
	 * Run method
	 * @note : Run parser on directories and add command lines arguments.
	 * @param argument_count : Command lines arguments count.
	 * @param argument_values : Command lines argument values.
	 **/
	void Run( const int32_t argument_count, const char** argument_values );

public:
	/**
	 * Register template method
	 * @note : Register an emitter to emitter list.
	 * @template Type : Query emitter type.
	 **/
	template<typename Type>
		requires ( std::is_base_of<MicroReflectEmitter, Type>::value )
	void Register( ) {
		if ( auto emitter = std::make_unique<Type>( ) )
			m_emitters.emplace_back( emitter );
	};

private:
	/**
	 * ProcessClang function
	 * @note : Parse source file with libclang.
	 * @param source_path : Query source file.
	 * @param declaration : Reference to the declaration storage.
	 **/
	bool ProcessClang( 
		const std::filesystem::path& source_path,
		MicroReflectSourceDeclaration& declaration 
	);

private:
	/**
	 * ClangVisitor static function
	 * @note : Represent Clang visitor function for source parsing phase.
	 * @param cursor : Current clang visitor cursor.
	 * @param parent : Current clang visitor parent cursor.
	 * @param user_data : Query user data.
	 * @return : Return clang visitor result value.
	 **/
	static CXChildVisitResult ClangVisitor(
		CXCursor cursor,
		CXCursor parent, 
		CXClientData user_data 
	);

private:
	/**
	 * CanParse function
	 * @note : Get if an extension match supported extension.
	 * @param extension : Query extension.
	 * @return : Return true when extension is found.
	 **/
	bool CanParse( const std::filesystem::path& extension ) const;

	/**
	 * GetArguments const function
	 * @note : Convert argument list to c-style string for libclang.
	 * @return : Return argument list as const char* list.
	 **/
	std::vector<const char*> GetArguments( ) const;

public:
	/**
	 * ClangGetString template function
	 * @note : Get string representation of a clang_get 'string' function.
	 * @template Args : Types of arguments used by the clang_get.
	 * @param clang_function : Query clang_get function to execute.
	 * @param args : Argument list for clang_get.
	 * @return : Return clang_get return value as c++ string.
	 **/
	template<
		typename... Args, 
		typename ClangSignature = std::function<CXString( Args... )>
	>
	static std::string ClangGetString(
		ClangSignature clang_function,
		const Args... args
	) {
		auto element_value  = std::invoke( clang_function, std::forward<Args>( args ) );
		auto element_string = clang_getCString( element_value );
		auto result			= std::string{ element_string };

		clang_disposeString( element_value );

		return std::move( result );
	};

};

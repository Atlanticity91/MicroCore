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

#include "Context/MicroReflectParsingContext.h"

/**
 * MicroReflectParser class
 * @note : Defined reflection system parser.
 **/
micro_class MicroReflectParser {

	using Emitter_t = std::unique_ptr<MicroReflectEmitter>;

private:
	MicroReflectParserReportModes m_report_mode;
	std::vector<std::string> m_extensions;
	std::vector<std::string> m_arguments;
	std::vector<std::string> m_directories;
	std::vector<Emitter_t> m_emitters;
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
	 * SetReportMode method
	 * @note : Set report mode.
	 * @param mode : Query report mode.
	 **/
	void SetReportMode( MicroReflectParserReportModes mode );

	/**
	 * InitializeGeneric method
	 * @note : Initialize parser with default extensions, arguments and options,
	 *		   ready for Micro reflection production.
	 **/
	void InitializeGeneric( );

	/**
	 * RegisterGeneric method
	 * @note : Register default emitters.
	 **/
	void RegisterGeneric( );

	/**
	 * AddArguments method
	 * @note : Parse command lines arguments.
	 * @param argument_count : Command lines arguments count.
	 * @param argument_values : Command lines argument values.
	 **/
	void ParseArguments( 
		const int32_t argument_count,
		micro_string* argument_values
	);

	/**
	 * Run method
	 * @note : Run parser on string source code.
	 * @param name : Query source name.
	 * @param source : Query source to parse.
	 **/
	void Run( const std::string& name, const std::string& source );

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
	void Run( const int32_t argument_count, micro_string* argument_values );

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
			m_emitters.emplace_back( std::move( emitter ) );
	};

protected:
	/**
	 * CreateTranslationUnit function
	 * @note : Wrapper for clang translation unit creation.
	 * @param clang_index : Query clang index.
	 * @param arguments : Query argument list.
	 * @param context : Query parser context.
	 * @param clang_unsaved : Query clang unsaved.
	 * @return : Return clang translation unit value.
	 **/
	CXTranslationUnit CreateTranslationUnit(
		CXIndex& clang_index,
		const std::vector<micro_string>& arguments,
		const MicroReflectParsingContext& context,
		CXUnsavedFile& clang_unsaved
	);

	/**
	 * CreateReport method
	 * @note : Create report for parsing context.
	 * @param clang_unit : Query clang translation unit.
	 * @param context : Query parsing context.
	 **/
	void CreateReport(
		const CXTranslationUnit& clang_unit,
		MicroReflectParsingContext& context
	);

	/**
	 * ProcessClang virtual function
	 * @note : Parse source file with libclang.
	 * @param arguments : Reference to argument list converted as native string list.
	 * @param context : Reference to the parsing context instance.
	 **/
	virtual bool ProcessClang(
		const std::vector<micro_string>& arguments,
		MicroReflectParsingContext& context,
		CXUnsavedFile& clang_unsaved
	);

	/**
	 * RunEmitters virtual method
	 * @note : Run parser emitters for context.
	 * @param context : Query reflection parsing context to execute.
	 **/
	virtual void RunEmitters( MicroReflectParsingContext& context );

	/**
	 * DumpReports method
	 * @note : Dump report for current context.
	 * @param context : Query parsing context.
	 **/
	virtual void DumpReports( MicroReflectParsingContext& context );

	/**
	 * RunParser virtual method
	 * @note : Run parser on specific file or directory.
	 * @param arguments : Reference to argument list converted as native string list.
	 * @param source_path : Query source path.
	 **/
	virtual void RunParser(
		const std::vector<micro_string>& arguments,
		const std::filesystem::path& source_path
	);

protected:
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
		Args&&... args
	) {
		auto element_value  = std::invoke( clang_function, std::forward<Args>( args )... );
		auto element_string = clang_getCString( element_value );
		auto result			= std::string{ element_string };

		clang_disposeString( element_value );

		return std::move( result );
	};

protected:
	/**
	 * CanParse function
	 * @note : Get if an extension match supported extension.
	 * @param extension : Query extension.
	 * @return : Return true when extension is found.
	 **/
	virtual bool CanParse( const std::filesystem::path& extension ) const;

	/**
	 * GetArguments const function
	 * @note : Convert argument list to c-style string for libclang.
	 * @return : Return argument list as native string list.
	 **/
	virtual std::vector<micro_string> GetArguments( ) const;

protected:
	/**
	 * GetIsFunction static function
	 * @note : Get if a clang cursor kind represent a function.
	 * @param cursor_kind : Query clang cursor kind.
	 * @return : Return true when cursor kind represent a function.
	 **/
	static bool GetIsFunction( const CXCursorKind cursor_kind );

};

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

#include "../../Containers/MicroDictionary.h"

/**
 * MicroLibraryProcedure class final
 * @note : Defined wrapper for dynamic library procedure interaction.
 **/
micro_class MicroLibraryProcedure final { 

	friend class MicroLibrary;

private:
	std::string m_name;
	void* m_callable;

public:
	/**
	 * Constructor
	 **/
	MicroLibraryProcedure( );

	/**
	 * Constructor
	 * @param name : Query procedure name.
	 **/
	MicroLibraryProcedure( const std::string& name );

public:
	/**
	 * GetIsCallable const function
	 * @note : Get if procedure is ready for call.
	 * @return : Return true when procedure is ready for calling.
	 **/
	bool GetIsCallable( ) const;

	/**
	 * GetName const function
	 * @note : Get procedure name.
	 * @return : Return procedure name value.
	 **/
	const std::string& GetName( ) const;

public:
	/**
	 * Cast operator
	 * @note : Get if procedure is ready for call.
	 * @return : Return GetIsCallable( ) call value.
	 **/
	operator bool ( ) const;

private:
	/**
	 * = operator
	 * @note : Asign procedure call pointer.
	 * @param callable : Procedure call pointer from library.
	 * @return : Return current procedure instance.
	 **/
	MicroLibraryProcedure& operator=( void* callable );

};

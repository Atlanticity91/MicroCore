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

#include "MicroLibraryProcedure.h"

#ifdef _WIN64
#	include <Windows.h>

typedef HMODULE MicroNativeHandle;
#else
extern "C" {
	#include <dlfcn.h>
};

typedef void* MicroNativeHandle;
#endif

/**
 * MicroLibrary final class
 * @note : Defined wrapper for dynamic library interaction.
 **/
micro_class MicroLibrary final {

private:
	MicroNativeHandle m_handle;
	bool m_is_local;
	std::string m_path;
	MicroLibraryProcedure m_root_procedure;

public:
	/**
	 * Constructor
	 **/
	MicroLibrary( );

	/**
	 * Constructor
	 * @param path : Query dynamic library path.
	 **/
	MicroLibrary( const std::string& path );

	/**
	 * Constructor
	 * @param path : Query dynamic library path.
	 * @param load_local : True for loading dynamic library on the caller process.
	 **/
	MicroLibrary( const std::string& path, bool load_local );

	/**
	 * Move-Constructor
	 **/
	MicroLibrary( MicroLibrary&& other );

	/**
	 * Destructor
	 **/
	~MicroLibrary( );

	/**
	 * Open function
	 * @note : Open dynamic library.
	 * @param path : Query dynamic library path.
	 * @param load_local : True for loading dynamic library on the caller process.
	 * @return : Return true when dynamic library opening succeeded.
	 **/
	bool Open( const std::string& path, bool load_local );

	/**
	 * Acquire function
	 * @note : Acquire procedure from the library.
	 * @param procedure : Query procedure to acquire.
	 * @return : Return procedure address value.
	 **/
	void* Acquire( const std::string& procedure );

	/**
	 * Acquire function
	 * @note : Acquire procedure from the library.
	 * @param procedure : Query procedure to acquire.
	 * @return : Return true when procedure acquisition succeeded.
	 **/
	bool Acquire( MicroLibraryProcedure& procedure );

	/**
	 * Release method
	 * @note : Release procedure.
	 * @param procedure : Query procedure to release.
	 **/
	void Release( MicroLibraryProcedure& procedure );

	/**
	 * Close function
	 * @note : Close dynamic library.
	 * @return : Return true when operation succeeded.
	 **/
	bool Close( );

private:
	/**
	 * FreeProcedures method
	 * @note : Free all procedure of the link list.
	 **/
	void FreeProcedures( );

public:
	/**
	 * AcquireAs template function
	 * @note : Acquire procedure from the library.
	 * @template Type : Query function pointer type.
	 * @param procedure : Query procedure to acquire.
	 * @return : Return procedure address value casted as function pointer.
	 **/
	template<typename Type>
		requires ( std::is_pointer<Type>::value )
	Type AcquireAs( const std::string& procedure ) { 
		return micro_cast( Acquire( procedure ), Type );
	};

public:
	/**
	 * GetIsValid const function
	 * @note : Get if library is valid.
	 * @return : Return true when library is valid.
	 **/
	bool GetIsValid( ) const;

	/**
	 * GetIsLocal const function
	 * @note : Get if library and is ressources are loaded on the caller process.
	 * @return : Return true when library is loaded on caller process.
	 **/
	bool GetIsLocal( ) const;

	/**
	 * GetPath const function
	 * @note : Get dynamic library file path.
	 * @return : Return dynamic library file path value.
	 **/
	const std::string& GetPath( ) const;

public:
	/**
	 * Cast operator 
	 * @note : Get if library is valid.
	 * @return : Return GetIsValid( ) call value.
	 **/
	operator bool ( ) const;

	/**
	 * [] operator
	 * @note : Acquire procedure from the library.
	 * @param procedure : Query procedure to acquire.
	 * @return : Return procedure address value.
	 **/
	void* operator[]( const std::string& procedure );

	/**
	 * [] operator
	 * @note : Acquire procedure from the library.
	 * @param procedure : Query procedure to acquire.
	 * @return : Return true when procedure acquisition succeeded.
	 **/
	bool operator[]( MicroLibraryProcedure& procedure );

};

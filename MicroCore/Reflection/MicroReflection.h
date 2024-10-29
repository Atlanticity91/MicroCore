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

#include "MicroReflectNative.h"

#define MICRO_FIELD( ... )
#define MICRO_FUNCTION( ... )
#define MICRO_ENUM( ... ) enum
#define MICRO_UNION( ... ) union 
#define MICRO_STRUCT( ... ) struct
#define MICRO_CLASS( ... ) class
#define MICRO_REFLECT_STRUCT( )\
	template<class T> \
	friend const micro::ReflectStruct* micro::GetStructImpl( micro::ReflectStructTag<T> ) noexcept;
#define MICRO_REFLECT_CLASS( )\
	template<class T> \
	friend const micro::ReflectClass* micro::GetClassImpl( micro::ReflectClassTag<T> ) noexcept;

namespace micro {

	/**
	 * GetType function
	 * @note : Get type implementation detail.
	 * @template T : Type to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectType* GetType( ) noexcept {
		return GetTypeImpl( ReflectTypeTag<T>{ } );
	};

	/**
	 * GetStruct function
	 * @note : Get struct implementation detail.
	 * @template T : Type of struct to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectStruct* GetStruct( ) noexcept {
		return GetStructImpl( ReflectStructTag<T>{ } );
	};

	/**
	 * GetClass function
	 * @note : Get class implementation detail.
	 * @template T : Type of class to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectClass* GetClass( ) noexcept {
		return GetClassImpl( ReflectClassTag<T>{ } );
	};

};

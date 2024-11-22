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

#include "MicroReflectImplementation.h"

namespace micro {

	#define REFLECT_TYPE( TYPE )\
		template<> extern const ReflectType* GetTypeImpl( ReflectTypeTag<TYPE> ) noexcept

	REFLECT_TYPE( void );
	REFLECT_TYPE( int8_t );
	REFLECT_TYPE( int16_t );
	REFLECT_TYPE( int32_t );
	REFLECT_TYPE( int64_t );
	REFLECT_TYPE( uint8_t );
	REFLECT_TYPE( uint16_t );
	REFLECT_TYPE( uint32_t );
	REFLECT_TYPE( uint64_t );
	REFLECT_TYPE( float );
	REFLECT_TYPE( double );
	REFLECT_TYPE( char );
	REFLECT_TYPE( bool );
	REFLECT_TYPE( std::string );
	REFLECT_TYPE( micro_string );

	template<>
	extern const ReflectClass* GetClassImpl( ReflectClassTag<std::string> ) noexcept;

	template<class T>
	extern const ReflectClass* GetClassImpl( ReflectClassTag<std::vector<T>> ) noexcept;

};

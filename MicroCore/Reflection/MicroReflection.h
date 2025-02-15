/**
 *
 *  __  __ _             ___
 * |  \/  (_)__ _ _ ___ / __|___ _ _ ___
 * | |\/| | / _| '_/ _ \ (__/ _ \ '_/ -_)
 * |_|  |_|_\__|_| \___/\___\___/_| \___|
 *
 * MIT License
 *
 * Copyright (c) 2024- Alves Quentin
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

/*
insert on premake build file

buildcommands {
	"MicroReflectParserName ..."
}
*/

#include "Tool/MicroReflectParser.h"

#ifndef __MICRO_REFLECT__
#	define MICRO_FIELD( ... )
#	define MICRO_FUNCTION( ... )
#	define MICRO_ENUM( ... ) enum
#	define MICRO_STRUCT( ... ) struct API
#	define MICRO_CLASS( ... ) class API
#	define MICRO_REFLECT_BODY( )\
		template<class T> \
		friend const micro::ReflectClass* micro_utils::get_class_impl( micro_utils::ReflectClassTag<T> ) noexcept;
#else
#	define MICRO_FIELD( ... ) __attribute__(( annotate( "micro_reflect," #__VA_ARGS__ )))
#	define MICRO_FUNCTION( ... ) __attribute__(( annotate( "micro_reflect," #__VA_ARGS__ )))
#	define MICRO_ENUM( ... ) enum __attribute__(( annotate( "micro_reflect," #__VA_ARGS__ )))
#	define MICRO_STRUCT( ... ) struct __attribute__(( annotate( "micro_reflect," #__VA_ARGS__ )))
#	define MICRO_CLASS( ... ) class __attribute__(( annotate( "micro_reflect," #__VA_ARGS__ )))
#	define MICRO_REFLECT_BODY( )
#endif

namespace micro {

	/**
	 * GetReflectType function
	 * @note : Get type implementation detail.
	 * @template T : Type to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectType* get_reflect_type( ) noexcept {
		return micro_utils::get_type_impl( micro_utils::ReflectTypeTag<T>{ } );
	};

	/**
	 * GetClass function
	 * @note : Get class implementation detail.
	 * @template T : Type of class to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectClass* get_reflect_class( ) noexcept {
		return micro_utils::get_class_impl( micro_utils::ReflectClassTag<T>{ } );
	};

};

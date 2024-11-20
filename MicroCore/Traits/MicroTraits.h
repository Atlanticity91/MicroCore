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

extern "C" {
	#include <stddef.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
};

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <concepts>
#include <condition_variable>
#include <filesystem>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <xhash>

/**
 * micro_cast macro
 * @note : Cast C style pointer to another pointer type.
 * @param VAR : Query source pointer.
 * @param TYPE : Query destination pointer type.
 **/
#define micro_cast( VAR, TYPE ) ( (TYPE)(VAR) )

/**
 * micro_ptr macro
 * @note : Get the address of a variable.
 * @param VAR : Query source variable.
 **/
#define micro_ptr( VAR ) ( &(VAR) )

/**
 * micro_ptr_as macro
 * @note : Get the address of a variable and cast result as TYPE*.
 * @param VAR : Query source variable.
 * @param TYPE : Query destination pointer type.
 **/
#define micro_ptr_as( VAR, TYPE ) micro_cast( micro_ptr( VAR ), TYPE )

/**
 * micro_ref macro
 * @note : Get reference from a C pointer.
 * @param VAR : s
 **/
#define micro_ref( VAR ) ( *(VAR) )

/**
 * micro_unused macro
 * @note : Mark function parameter unused for the compiler.
 **/
#define micro_unused( VAR ) ( (void)VAR )

/**
 * micro_compile_if macro
 * @note : Wrapper for Compile time if dispatch.
 **/
#define micro_compile_if( ... ) if constexpr ( __VA_ARGS__ ) 

/**
 * micro_compile_elif macro
 * @note : Wrapper for Compile time else if dispatch.
 **/
#define micro_compile_elif( ... ) else micro_compile_if( __VA_ARGS__ )

/**
 * micro_compile_else macro
 * @note : Wrapper for Compile time else dispatch.
 **/
#define micro_compile_else else

/**
 * micro_depreated macro
 * @note : Mark element deprecated with since message.
 **/
#define micro_depreated( SINCE ) [[deprecated( "Since : " micro_stringify( SINCE ) )]]

/**
 * micro_depreated_for macro
 * @note : Mark element deprecated with since message and replacement indication.
 **/
#define micro_depreated_for( SINCE, REPLACEMENT )\
	[[deprecated( "Since : " micro_stringify( SINCE ) ", instead use : " micro_stringify( REPLACEMENT ) )]]

/**
 * micro_nodiscard_cause macro
 * @note : Mark that function return value can't be discarded with cause message.
 * @param MESSAGE : Cause of non discard.
 **/
#define micro_nodiscard_cause( MESSAGE ) [[nodiscard( MESSAGE )]]

/**
 * micro_nodiscard macro
 * @note : Mark that function return value can't be discarded.
 **/
#define micro_nodiscard [[nodiscard]]

/**
 * micro_self macro
 * @note : Wrapper for class member function *this.
 **/
#define micro_self micro_ref( this )

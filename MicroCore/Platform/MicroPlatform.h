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

#include "../Traits/Profilers/MicroProfiler.h"

namespace micro {

	/**
	 * is_little_endian function
	 * @note : Get if plaform is little endian.
	 * @return : True when plaform is little endian.
	 **/
	MICRO_API bool is_little_endian( );

	/**
	 * copy function
	 * @note : Wrapper for platform memcpy.
	 * @param length : Length of the source and destination buffer.
	 * @param src : Pointer to the source buffer.
	 * @param dst : Pointer to the destination buffer.
	 * @return : True for copy success.
	 **/
	MICRO_API bool copy( const uint32_t length, const void* src, void* dst );
	
	/**
	 * move function
	 * @note : Wrapper for platform memmove.
	 * @param length : Length of the source and destination buffer.
	 * @param src : Pointer to the source buffer.
	 * @param dst : Pointer to the destination buffer.
	 * @return : True for copy success.
	 **/
	MICRO_API bool move( const uint32_t length, const void* src, void* dst );

	/**
	 * copy template function
	 * @note : Template wrapper for the memcopy function.
	 * @param template Type : Type of the element to copy.
	 * @param src : Reference to the source.
	 * @param dst : Reference to the destination. 
	 * @return : True for copy success.
	 **/
	template<typename Type>
	bool copy( const Type& src, Type& dst ) { 
		return copy( (uint32_t)sizeof( Type ), micro_ptr( src ), micro_ptr( dst ) );
	};

	/**
	 * move template function
	 * @note : Template wrapper for the memmove function.
	 * @param template Type : Type of the element to move.
	 * @param src : Reference to the source.
	 * @param dst : Reference to the destination.
	 * @return : True for copy success.
	 **/
	template<typename Type>
	bool move( const Type& src, Type& dst ) {
		return move( (uint32_t)sizeof( Type ), micro_ptr( src ), micro_ptr( dst ) );
	};

	/**
	 * swap_endianness method
	 * @note : Swap data endianness to current platform endianness.
	 * @template Type : Query type of data to swap.
	 * @param data : Reference to query data to swap.
	 **/
	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	inline void swap_endianness( Type& data ) {
		auto data_size = sizeof( Type );
		auto byte_max  = data_size / 2;
		auto byte_id   = (size_t)0;

		while ( byte_id < byte_max ) {
			std::swap( data[ byte_id ], data[ data_size - byte_id - 1 ] );

			byte_id += 1;
		}
	};

	/**
	 * swap_endianness method
	 * @note : Swap data array endianness to current platform endianness.
	 * @template Type : Query type of data to swap.
	 * @param length : Query data array length.
	 * @param data : Reference to query data array to swap.
	 **/
	template<typename Type>
		requires ( std::is_pointer<Type>::value )
	inline void swap_endianness( const uint32_t length, Type& data ) {
		auto element_id = length;
		
		while ( element_id-- > 0 )
			swap_endianness( data[ element_id ] );
	};

};

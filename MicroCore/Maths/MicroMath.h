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

#include "MicroInterpolation.h"

namespace micro {

	/**
	 * crc32 function
	 * @note : Calculate CRC 32 bits for checksum validation.
	 * @param data : Data used to calculate the checksum value.
	 **/
	micro_nodiscard_cause( "Cyclic Redundancy Checksum calculation is expensive" ) 
	micro_nodiscard MICRO_API uint32_t crc32( const std::vector<uint8_t>& data );

	/**
	 * crc32 function
	 * @note : Calculate CRC 32 bits for checksum validation.
	 * @param length : Length of data buffer.
	 * @param pointer : Pointer to data buffer.
	 **/
	micro_nodiscard_cause( "Cyclic Redundancy Checksum calculation is expensive" )
	micro_nodiscard MICRO_API uint32_t crc32( const uint32_t length, const uint8_t* pointer );
	
	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint32_t hash32( const std::string& string );

	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint32_t hash32( micro_string string );

	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param length : Length of string to hash.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint32_t hash32( const uint32_t length, micro_string string );

	/**
	 * hash64 function
	 * @note : Calculate 64 bits based hash for string.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint64_t hash64( const std::string& string );

	/**
	 * hash32 function
	 * @note : Calculate 64 bits based hash for string.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint64_t hash64( micro_string string );

	/**
	 * hash64 function
	 * @note : Calculate 64 bits based hash for string.
	 * @param length : Length of string to hash.
	 * @param string : String to hash.
	 **/
	micro_nodiscard_cause( "Hashing string is expensive" )
	micro_nodiscard MICRO_API uint64_t hash64( const uint32_t length, micro_string string );

};
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

#include "../Platform/MicroFile.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

typedef glm::uvec2 micro_upoint;
typedef glm::i32vec2 micro_point;
typedef glm::vec2 micro_vec2;
typedef glm::vec3 micro_vec3;
typedef glm::vec4 micro_vec4;
typedef glm::mat3 micro_mat3;
typedef glm::mat4 micro_mat4;

namespace micro {

	/**
	 * crc32 function
	 * @note : Calculate CRC 32 bits for checksum validation.
	 * @param data : Data used to calculate the checksum value.
	 **/
	uint32_t crc32( const std::vector<uint8_t>& data );

	/**
	 * crc32 function
	 * @note : Calculate CRC 32 bits for checksum validation.
	 * @param length : Length of data buffer.
	 * @param pointer : Pointer to data buffer.
	 **/
	uint32_t crc32( const uint32_t length, const uint8_t* pointer );
	
	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param string : String to hash.
	 **/
	uint32_t hash32( const std::string& string );

	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param string : String to hash.
	 **/
	uint32_t hash32( micro_string string );

	/**
	 * hash32 function
	 * @note : Calculate 32 bits based hash for string.
	 * @param length : Length of string to hash.
	 * @param string : String to hash.
	 **/
	uint32_t hash32( const uint32_t length, micro_string string );

};

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

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace micro {

	template<>
	const ReflectStruct* GetStructImpl( ReflectStructTag<micro_vec4> ) noexcept {
		static auto storage_vec4 = ReflectStorageStruct<micro_vec4, 4>{
			"micro_vec4",
			[]( auto* self ) {
				self->Fields[ 0 ] = { "x", GetType<micro_vec2::value_type>( ) };
				self->Fields[ 1 ] = { "y", offsetof( micro_vec4, y ), GetType<micro_vec2::value_type>( ) };
				self->Fields[ 2 ] = { "z", offsetof( micro_vec4, z ), GetType<micro_vec2::value_type>( ) };
				self->Fields[ 3 ] = { "w", offsetof( micro_vec4, w ), GetType<micro_vec2::value_type>( ) };
			}
		};

		return storage_vec4;
	};

};

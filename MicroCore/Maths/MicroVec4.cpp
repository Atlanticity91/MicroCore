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

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		=== OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
bool operator==( const micro_vec4& vector, const float scalar ) {
	return vector.x == scalar && vector.y == scalar && vector.z == scalar && vector.w == scalar;
}

bool operator!=( const micro_vec4& vector, const float scalar ) {
	return !( vector == scalar );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace micro_utils {

	template<>
	const micro::ReflectClass* get_class_impl( ReflectClassTag<micro_vec4> ) noexcept {
		static auto storage_vec4 = micro::ReflectStorageClass<micro_vec4, 0, 4, 0>{
			"micro_vec4",
			[]( auto* self ) {
				self->Fields[ 0 ] = { "x", micro::get_reflect_type<micro_vec4::value_type>( ) };
				self->Fields[ 1 ] = { "y", offsetof( micro_vec4, y ), micro::get_reflect_type<micro_vec4::value_type>( ) };
				self->Fields[ 2 ] = { "z", offsetof( micro_vec4, z ), micro::get_reflect_type<micro_vec4::value_type>( ) };
				self->Fields[ 3 ] = { "w", offsetof( micro_vec4, w ), micro::get_reflect_type<micro_vec4::value_type>( ) };
			}
		};

		return storage_vec4;
	};

};

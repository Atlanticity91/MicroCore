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
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace micro_utils {

	#define REFLECT_TYPE_IMP( TYPE )\
		template<> const micro::ReflectType* get_type_impl( ReflectTypeTag<TYPE> ) noexcept {\
			static auto type_info = micro::ReflectType{ micro_stringify( TYPE ), micro_sizeof( TYPE ) };\
			return micro_ptr( type_info );\
		}

	template<>
	const micro::ReflectType* get_type_impl( ReflectTypeTag<void> ) noexcept {
		static auto void_type = micro::ReflectType{ "void", 0 };

		return micro_ptr( void_type );
	}

	REFLECT_TYPE_IMP( int8_t );
	REFLECT_TYPE_IMP( int16_t );
	REFLECT_TYPE_IMP( int32_t );
	REFLECT_TYPE_IMP( int64_t );
	REFLECT_TYPE_IMP( uint8_t );
	REFLECT_TYPE_IMP( uint16_t );
	REFLECT_TYPE_IMP( uint32_t );
	REFLECT_TYPE_IMP( uint64_t );
	REFLECT_TYPE_IMP( float );
	REFLECT_TYPE_IMP( double );
	REFLECT_TYPE_IMP( char );
	REFLECT_TYPE_IMP( bool );

	template<>
	const micro::ReflectType* get_type_impl( ReflectTypeTag<std::string> ) noexcept {
		static auto type_info = micro::ReflectType{ "std::string", micro_sizeof( std::string ) };

		return micro_ptr( type_info );
	}

	template<>
	const micro::ReflectType* get_type_impl( ReflectTypeTag<micro_string> ) noexcept {
		static auto type_info = micro::ReflectType{ "const char*", micro_sizeof( micro_string ) };

		return micro_ptr( type_info );
	}

	template<>
	const micro::ReflectClass* get_class_impl( ReflectClassTag<std::string> ) noexcept {
		static auto storage_string = micro::ReflectStorageClass<std::string, 0, 0, 0>{
			"std::string" 
		};

		return storage_string;
	}

};

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

	#define REFLECT_TYPE_IMP( TYPE )\
		template<> const ReflectType* GetTypeImpl( ReflectTypeTag<TYPE> ) noexcept {\
			static auto type_info = ReflectType{ micro_stringify( TYPE ), sizeof( TYPE ) };\
			return &type_info;\
		}

	template<>
	const ReflectType* GetTypeImpl( ReflectTypeTag<void> ) noexcept {
		static auto void_type = ReflectType{ "void", 0 };

		return &void_type;
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
	const ReflectType* GetTypeImpl( ReflectTypeTag<std::string> ) noexcept {
		static auto type_info = ReflectType{ "std::string", sizeof( std::string ) };

		return &type_info;
	}

	template<>
	const ReflectType* GetTypeImpl( ReflectTypeTag<micro_string> ) noexcept {
		static auto type_info = ReflectType{ "const char*", sizeof( micro_string ) };

		return &type_info;
	}

	template<>
	const ReflectClass* GetClassImpl( ReflectClassTag<std::string> ) noexcept {
		static auto storage_string = ReflectStorageClass<std::string, 0, 0, 0>{
			"std::string",
			[]( auto* self ) { }
		};

		return storage_string;
	}

	template<class T>
	const ReflectClass* GetClassImpl( ReflectClassTag<std::vector<T>> ) noexcept {
		static auto storage_vector = ReflectStorageClass<std::vector<T>, 0, 0, 0>{
			"std::vector",
			[]( auto* self ) { }
		};

		return storage_vector;
	}

};

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

#include "MicroTestable.h"

namespace micro {

	/**
	 * are_equal template function
	 * @note : Wrapper for == operator call.
	 * @template AType : Query left operand type.
	 * @template BType : Query right operand type.
	 * @return : Return == call value when operator is present and false otherwise.
	 **/
	template<typename AType, typename BType>
	bool are_equal( const AType& one, const BType& two ) {
		micro_compile_if( std::equality_comparable<AType, BType>::value )
			return one == two;
		micro_compile_else
			return false;
	};

	/**
	 * are_not_equal template function
	 * @note : Wrapper for != operator call.
	 * @template AType : Query left operand type.
	 * @template BType : Query right operand type.
	 * @return : Return != call value when operator is present and false otherwise.
	 **/
	template<typename AType, typename BType>
	bool are_not_equal( const AType& one, const BType& two ) {
		micro_compile_if( std::equality_comparable<AType, BType>::value )
			return one != two;
		micro_compile_else
			return false;
	};

	/**
	 * to_string template function
	 * @note : Get string representation of Type.
	 * @template : Query Type.
	 * @return : Return string representation of element.
	 **/
	template<typename Type>
	micro_inline std::string to_string( ) {
		return { micro_stringify( Type ) };
	};

	/**
	 * to_string template function
	 * @note : Get string representation of element.
	 * @template : Query element type.
	 * @param element : Query element.
	 * @return : Return string representation of element.
	 **/
	template<typename Type>
	std::string to_string( const Type& element ) {
		micro_compile_if( std::is_base_of<MicroTestable<Type>, Type>::value )
			return std::move( element.GetAsString( ) );
		micro_compile_else
			return to_string<Type>( );
	};

};

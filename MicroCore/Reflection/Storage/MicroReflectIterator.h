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

#include "../Types/MicroReflectField.h"

namespace micro {

	template<class T>
	struct MicroReflectIterator {

		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type		= T;
		using pointer			= T*;
		using reference			= T&;

	private:
		pointer m_value;

	public:
		/**
		 * Constructor
		 **/
		MicroReflectIterator( )
			: MicroReflectIterator{ nullptr } 
		{ };

		/**
		 * Constructor
		 * @param value : Query iterator current value.
		 **/
		MicroReflectIterator( pointer value )
			: m_value{ value }
		{ };

		/**
		 * Dereference operator
		 * @note : Convert iterator to reference of T.
		 * @return : Return const reference to internal value.
		 **/
		const reference operator*( ) const {
			return *m_value;
		};

		/**
		 * Member access operator
		 * @note : Access member element of internal value.
		 * @return : Return const pointer of internal value.
		 **/
		const pointer operator->( ) {
			return m_value;
		};

		/**
		 * Prefix increment operator
		 * @note : Prefix increment current iterator.
		 * @return : Return reference to current incremented iterator.
		 **/
		MicroReflectIterator& operator++( ) {
			m_value++;

			return *this;
		};

		/**
		 * Postfix increment operator
		 * @note : Postfix increment current iterator.
		 * @return : Return iterator berfore incrementation.
		 **/
		MicroReflectIterator operator++( int ) {
			MicroReflectIterator tmp = *this;

			++( *this );

			return tmp;
		};

		/**
		 * Asign operator
		 * @note : Asign iterator value.
		 * @param other : Other iterator.
		 * @return : Return reference to current iterator.
		 **/
		MicroReflectIterator& operator=( const MicroReflectIterator& other ) {
			m_value = other.m_value;

			return *this;
		};

		/**
		 * Equal operator
		 * @note : Check if two iterator are equal.
		 * @param iterator_a : First iterator.
		 * @param iterator_b : Second iterator.
		 * @return : Return true when the two iterator match.
		 **/
		friend bool operator==(
			const MicroReflectIterator& iterator_a,
			const MicroReflectIterator& iterator_b
		) {
			return iterator_a.m_value == iterator_b.m_value;
		};

		/**
		 * Not equal operator
		 * @note : Check if two iterator aren't equal.
		 * @param iterator_a : First iterator.
		 * @param iterator_b : Second iterator.
		 * @return : Return true when the two iterator match.
		 **/
		friend bool operator!=(
			const MicroReflectIterator& iterator_a,
			const MicroReflectIterator& iterator_b
		) {
			return iterator_a.m_value != iterator_b.m_value;
		};

	};

};

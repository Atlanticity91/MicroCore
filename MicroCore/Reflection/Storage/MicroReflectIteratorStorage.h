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

#include "MicroReflectIterator.h"

namespace micro {

	template<class T>
	class MicroReflectIteratorStorage {

	public:
		using Iterator_t		= MicroReflectIterator<T>;
		using IteratorPointer_t = typename Iterator_t::pointer;

	private:
		Iterator_t m_first;
		Iterator_t m_last;
		uint32_t m_count;

	public:
		/**
		 * Constructor
		 **/
		MicroReflectIteratorStorage( )
			: MicroReflectIteratorStorage( nullptr, 0 ) 
		{ };

		/**
		 * Constructor
		 * @param first : First element of the iteration.
		 * @param count : Count of element to iterate.
		 **/
		MicroReflectIteratorStorage( const IteratorPointer_t first, const uint32_t count )
			: m_first{ first },
			m_last{ first + count },
			m_count{ count }
		{ };

		/**
		 * GetIsValid const function
		 * @note : Get if iterator storage is valid.
		 * @return : Return true when iterator storage is valid.
		 **/
		bool GetIsValid( ) const {
			return m_first != m_last;
		};

		/**
		 * GetCount const function
		 * @note : Get iterator element count.
		 * @return : Return current iterator element count.
		 **/
		uint32_t GetCount( ) const {
			return m_count;
		};

		/**
		 * begin const function
		 * @note : Begin function for generic c++ for loop, get first element.
		 * @return : Return pointer to first element of the iteration.
		 **/
		const Iterator_t begin( ) const {
			return m_first;
		};

		/**
		 * end const function
		 * @note : End function for generic c++ for loop, get last element.
		 * @return : Return pointer to last element of the iteration.
		 **/
		const Iterator_t end( ) const {
			return m_last;
		};

		/**
		 * Asign operator
		 * @note : Asign iterator storage.
		 * @param other : Other iterator storage.
		 * @return : Return reference to current iterator storage.
		 **/
		MicroReflectIteratorStorage& operator=( const MicroReflectIteratorStorage& other ) {
			m_first = other.begin( );
			m_last  = other.end( );

			return micro_self;
		};

		/**
		 * Cast operator
		 * @note : Get if iterator storage is valid.
		 * @return : Return GetIsValid( ) call value.
		 **/
		operator bool( ) const {
			return GetIsValid( );
		};

	};

};

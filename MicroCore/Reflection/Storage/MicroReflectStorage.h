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

#include "MicroReflectIteratorStorage.h"

namespace micro {

	template<class T, size_t Count>
	struct ReflectStorage {

		using IteratorStorage_t = MicroReflectIteratorStorage<T>;
		using IteratorPointer_t = typename IteratorStorage_t::IteratorPointer_t;

		T Elements[ micro_array_size<Count> ];

		/**
		 * constructor
		 **/
		ReflectStorage( )
			: ReflectStorage{ { } }
		{ };

		/**
		 * constructor
		 * @param elements : List of all elements as initializer_list.
		 **/
		ReflectStorage( std::initializer_list<T> elements )
			: Elements{ }
		{
			auto* element_array = elements.begin( );
			auto element_id		= elements.size( );

			while ( element_id-- > 0 )
				micro::move( element_array[ element_id ], Elements[ element_id ] );
		};

		/**
		 * GetIteratorStorage const function
		 * @note : Get iterator storage for current storage.
		 * @return : Return iterator storage representation.
		 **/
		const IteratorStorage_t GetIteratorStorage( ) const {
			return IteratorStorage_t{ (IteratorPointer_t)Elements, Count };
		};

		/**
		 * Access operator
		 * @param elment_id : Index of the query element in range [ 0 : Count - 1 ].
		 * @return : Return reference to query element.
		 **/
		T& operator[]( const size_t element_id ) {
			micro_assert( element_id < Count, "You can't access element outside storage range [ 0 : %u ]", Count - 1 );

			return Elements[ element_id ];
		};

		/**
		 * Cast operator
		 * @note : Cast current storage to it's iterator storage representation.
		 * @return : Return GetIteratorStorage( ) call value.
		 **/
		operator const IteratorStorage_t( ) const {
			return GetIteratorStorage( );
		};

	};

};

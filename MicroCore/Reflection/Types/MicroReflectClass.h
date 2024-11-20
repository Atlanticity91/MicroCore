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

#include "ReflectParent.h"

namespace micro { 

	struct ReflectClass : public ReflectType {

		using Parent_t	  = MicroReflectIteratorStorage<ReflectParent>;
		using Fields_t	  = MicroReflectIteratorStorage<ReflectField>;
		using Functions_t = MicroReflectIteratorStorage<ReflectFunction>;

		Parent_t Parents;
		Fields_t Fields;
		Functions_t Functions;

		/**
		 * Constructor
		 **/
		ReflectClass( );

		/**
		 * Constructor
		 * @param name : Name of the class.
		 * @param size : Size of the class.
		 * @param fields : Query class field iterator storage.
		 * @param functions : Query class function iterator storage.
		 **/
		ReflectClass(
			micro_string name,
			const size_t size
		);

		/**
		 * Constructor
		 * @param name : Name of the class.
		 * @param size : Size of the class.
		 * @param fields : Query class field iterator storage.
		 * @param functions : Query class function iterator storage.
		 **/
		ReflectClass(
			micro_string name,
			const size_t size,
			const Fields_t fields,
			const Functions_t functions
		);

		/**
		 * Constructor
		 * @param name : Name of the class.
		 * @param size : Size of the class.
		 * @param parents : Query class parents.
		 * @param fields : Query class field iterator storage.
		 * @param functions : Query class function iterator storage.
		 **/
		ReflectClass( 
			micro_string name,
			const size_t size,
			const Parent_t parents,
			const Fields_t fields,
			const Functions_t functions
		);

	};

};

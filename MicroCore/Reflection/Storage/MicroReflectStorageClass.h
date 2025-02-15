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

#include "../Types/MicroReflectClass.h"

namespace micro { 

	template<class T, uint32_t ParentCount, uint32_t FieldCount, uint32_t FunctionCount>
	struct ReflectStorageClass {

		ReflectStorage<ReflectParent, ParentCount> Parents;
		ReflectStorage<ReflectField, FieldCount> Fields;
		ReflectStorage<ReflectFunction, FunctionCount> Functions;
		ReflectClass Detail;

		/**
		 * Constructor
		 * @param name : Name of the class.
		 **/
		ReflectStorageClass( micro_string name )
			: ReflectStorageClass{ name, []( auto* ) { } }
		{ };

		/**
		 * Constructor
		 * @template Lambda : Lambda signature taking pointer to self.
		 * @param name : Name of the class.
		 * @param lambda : Query construction lambda.
		 **/
		template<typename Lambda>
		ReflectStorageClass( micro_string name, Lambda&& lambda )
			: Detail{ name, micro_sizeof( T ) }
		{
			std::invoke( lambda, this );
			
			Detail.Parents   = Parents;
			Detail.Fields	 = Fields;
			Detail.Functions = Functions;
		};

		/**
		 * Cast operator
		 * @note : Get pointer to class detail information.
		 * @return : Return pointer to class detail.
		 **/
		operator const ReflectClass* ( ) const {
			return micro_ptr( Detail );
		};

	};

};

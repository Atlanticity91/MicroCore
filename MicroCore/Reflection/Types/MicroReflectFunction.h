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

#include "MicroReflectFunctionParameter.h"

namespace micro { 

	/**
	 * ReflectFunction struct
	 * @note : Defined function representation for reflection system.
	 **/
	micro_struct ReflectFunction : public ReflectType {

		using Parameters_t = MicroReflectIteratorStorage<ReflectFunctionParameter>;

		MicroReflectAccessor Accessor;
		const ReflectType* ReturnType;
		Parameters_t Parameters;

		/**
		 * Constructor
		 **/
		ReflectFunction( );

		/**
		 * Constructor
		 * @param name : Name of the function.
		 **/
		ReflectFunction( micro_string name );

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param accessor : Query field accessor.
		 **/
		ReflectFunction( 
			micro_string name,
			const MicroReflectAccessor accessor
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param return_type : Type of the function return value.
		 **/
		ReflectFunction(
			micro_string name,
			const ReflectType* return_type
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param parameters : Iterator storage for the parameters.
		 **/
		ReflectFunction(
			micro_string name,
			const Parameters_t parameters
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param accessor : Query field accessor.
		 * @param return_type : Type of the function return value.
		 **/
		ReflectFunction(
			micro_string name,
			const MicroReflectAccessor accessor,
			const ReflectType* return_type
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param accessor : Query field accessor.
		 * @param parameters : Iterator storage for the parameters.
		 **/
		ReflectFunction(
			micro_string name,
			const MicroReflectAccessor accessor,
			const Parameters_t parameters
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param return_type : Type of the function return value.
		 * @param parameters : Iterator storage for the parameters.
		 **/
		ReflectFunction(
			micro_string name,
			const ReflectType* return_type,
			const Parameters_t parameters
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param accessor : Query field accessor.
		 * @param return_type : Type of the function return value.
		 * @param parameters : Iterator storage for the parameters.
		 **/
		ReflectFunction(
			micro_string name,
			const MicroReflectAccessor accessor,
			const ReflectType* return_type,
			const Parameters_t parameters
		);

		/**
		 * Constructor
		 * @param name : Name of the function.
		 * @param accessor : Query field accessor.
		 * @param return_type : Type of the function return value.
		 * @param lambda : Function lambda to generate function parameters storage.
		 **/
		ReflectFunction(
			micro_string name,
			const MicroReflectAccessor accessor,
			const ReflectType* return_type,
			std::function<Parameters_t()> lambda
		);

	};

};

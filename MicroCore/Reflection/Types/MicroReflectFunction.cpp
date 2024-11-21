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

	ReflectFunction::ReflectFunction( )
		: ReflectFunction{ "", MicroReflectAccessor::Public, GetReflectType<void>( ) }
	{ }

	ReflectFunction::ReflectFunction( micro_string name )
		: ReflectFunction{ 
			name, 
			MicroReflectAccessor::Public, 
			GetReflectType<void>( ), 
			Parameters_t{ } 
		}
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const MicroReflectAccessor accessor
	)
		: ReflectFunction{ name, accessor, GetReflectType<void>( ), Parameters_t{ } }
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const ReflectType* return_type
	)
		: ReflectFunction{ 
			name, 
			MicroReflectAccessor::Public,
			return_type,
			Parameters_t{ } 
		}
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const Parameters_t parameters
	) 
		: ReflectFunction{
			name, 
			MicroReflectAccessor::Public,
			GetReflectType<void>( ), 
			parameters 
		}
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const MicroReflectAccessor accessor,
		const ReflectType* return_type
	)
		: ReflectFunction{ name, accessor, return_type, Parameters_t{ } }
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const MicroReflectAccessor accessor,
		const Parameters_t parameters
	)
		: ReflectFunction{ name, accessor, GetReflectType<void>( ), parameters }
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const ReflectType* return_type,
		const Parameters_t parameters
	)
		: ReflectFunction{ name, MicroReflectAccessor::Public, return_type, parameters }
	{ }

	ReflectFunction::ReflectFunction(
		micro_string name,
		const MicroReflectAccessor accessor,
		const ReflectType* return_type,
		const Parameters_t parameters
	)
		: ReflectType{ name },
		Accessor{ accessor },
		ReturnType{ return_type },
		Parameters{ parameters }
	{
		Size = parameters.GetCount( );
	}

	ReflectFunction::ReflectFunction(
		micro_string name,
		const MicroReflectAccessor accessor,
		const ReflectType* return_type,
		std::function<Parameters_t( )> lambda
	)
		: ReflectFunction{ name, accessor, return_type, Parameters_t{ } }
	{
		Parameters = std::invoke( lambda );
		Size	   = Parameters.GetCount( );
	}

};

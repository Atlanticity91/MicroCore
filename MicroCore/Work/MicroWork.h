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

#include "../Yaml/MicroYamlWriter.h"

/**
 * MicroWorkRequirements concept
 * @note : Defined requirements for a type to be store in the work cache.
 **/
template<typename Type>
concept MicroWorkRequirements = ( sizeof( Type ) <= sizeof( float ) * 16 );

/**
 * MicroWork struct
 * @note : Defined thread work handle.
 **/
micro_struct MicroWork {
	
	using Execute_t  = std::function<bool( class MicroWorkManager*, float* )>;
	using Callback_t = std::function<void( class MicroWorkManager*, float* )>;

	Execute_t Execute;
	Callback_t OnSucced;
	Callback_t OnFailed;
	float Storage[ 16 ];

	/**
	 * Constructor
	 **/
	MicroWork( );

	/**
	 * Constructor
	 * @note : Defined work execution function, and no success or failure callback.
	 * @param execute : Work execution function based on the Execute_t prototype.
	 **/
	MicroWork( Execute_t execute );

	/**
	 * Constructor
	 * @note : Defined work execution function with success and failure callback.
	 * @param execute : Work execution function based on the Execute_t prototype.
	 * @param on_succed : Success function based on the Callback_t prototype.
	 * @param on_failed : Failure function based on the Callback_t prototype.
	 **/
	MicroWork( Execute_t execute, Callback_t on_succed, Callback_t on_failed );

	/**
	 * Constructor template
	 * @template Type : Type of data to store inside the work, with maximum size
	 *					of a 16 float matrix.
	 * @param execute : Work execution function based on the Execute_t prototype.
	 * @param data : Reference to the data to store.
	 **/
	template<typename Type>
		requires MicroWorkRequirements<Type>
	MicroWork( Execute_t execute, const Type& data ) 
		: MicroWork{ execute }
	{ 
		micro::move( (uint32_t)sizeof( Type ), &data, Storage );
	};

	/**
	 * Constructor template
	 * @template Type : Type of data to store inside the work, with maximum size
	 *					of a 16 float matrix.
	 * @note : Defined work execution function with success and failure callback.
	 * @param execute : Work execution function based on the Execute_t prototype.
	 * @param on_succed : Success function based on the Callback_t prototype.
	 * @param on_failed : Failure function based on the Callback_t prototype.
	 * @param data : Reference to the data to store.
	 **/
	template<typename Type>
		requires MicroWorkRequirements<Type>
	MicroWork( Execute_t execute, Callback_t on_succed, Callback_t on_failed, const Type& data )
		: MicroWork{ execute, on_succed, on_failed }
	{
		micro::move( (uint32_t)sizeof( Type ), &data, Storage );
	};

	/**
	 * GetIsValid const function
	 * @note : Get if the work is valid.
	 * @return : True for valid work.
	 **/
	bool GetIsValid( ) const;

	/**
	 * bool cast operator
	 * @note : Cast current work to boolean to ensure validity.
	 **/
	operator bool( ) const;

};

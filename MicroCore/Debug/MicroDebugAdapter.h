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

#include "Events/MicroDebugEventThread.h"

micro_struct MicroDebugAdapterBuffer {

	uint32_t Length;
	uint32_t Size;
	const char* Data;

};

micro_class MicroDebugAdapter final {

public:
	static MicroDebugAdapterError Connect( 
		const MicroDebugAdapterSpecification& specification
	);

	static MicroDebugAdapterError Broadcast( 
		const MicroDebugEvent* event_specification 
	);

	static MicroDebugAdapterError Receive( MicrDebugEventTypes& event_type );

	static MicroDebugAdapterError Disconnect( );

public:
	template<typename Type>
		requires ( 
			!std::is_pointer_v<Type> && 
			std::is_base_of_v<MicroDebugEvent, Type>
		)
	static MicroDebugAdapterError Broadcast( const Type& event_specification ) { 
		return Broadcast( micro_ptr( event_specification ) );
	};

public:
	static uint32_t GetBufferSize( );

	static const char* GetBufferData( );

	static const MicroDebugAdapterBuffer GetBuffer( );

	static const std::string ToString( const MicroDebugMessageTypes type );

	static const std::string ToString( const bool value );

	static const std::string ToString( const MicroDebugEventReasons reason );

};

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

#include "../Work/MicroWorkManager.h"

/**
 * MICRO_LOCAL_IP_STRING macro
 * @note : Dfine localhost ip-v4 address as string.
 **/
#define MICRO_LOCAL_IP_STRING "127.0.0.1"

/**
 * MICRO_DEBUG_VS_PORT macro
 * @note : Define default visual studio debugging network port.
 **/
#define MICRO_DEBUG_VS_PORT 12345

/**
 * MICRO_DEBUG_VSC_PORT macro
 * @note : Define default visual studio CODE debugging network port.
 **/
#define MICRO_DEBUG_VSC_PORT 12345

struct MicroDebugAdapterSpecification {

	micro_string Address;
	uint16_t Port;

	MicroDebugAdapterSpecification( );

	MicroDebugAdapterSpecification( micro_string address );

	MicroDebugAdapterSpecification( const uint16_t port );

	MicroDebugAdapterSpecification( micro_string address, const uint16_t port );

};

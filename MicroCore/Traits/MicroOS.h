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

#include "MicroArchitecture.h"

#if defined( _WIN32 ) || defined( _WIN64 ) || defined( __MINGW32__ ) || defined( __MINGW64__ ) || defined( __CYGWIN__ )
#	define MICRO_OS_WINDOWS
#elif defined( __linux__ ) || defined( __unix__ ) || defined( __FreeBSD__ )
#	define MICRO_OS_LINUX
#elif defined( __ANDROID__ )
#	define MICRO_OS_ANDROID
#elif defined( __APPLE__ ) 
#	if defined( __MACH__ )
#		define MICRO_OS_MACOS
#	else
#		define MICRO_OS_IOS
#	endif
#else
#	throw "OS undefined"
#endif

micro_struct MicroOSSpecification final {

	std::string Name;
	std::string Version;
	std::string Architecture;
	uint32_t Ram;
	uint32_t Cores;

	MicroOSSpecification( );

	MicroOSSpecification( MicroOSSpecification&& other ) noexcept;

};

namespace micro {

	MICRO_API MicroOSSpecification get_os_specification( );

};

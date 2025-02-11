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

#include "MicroTraits.h"

/**
 *    from:
 *        https://github.com/cpredef/predef/blob/master/Architectures.md
 *        https://github.com/boostorg/predef/blob/develop/include/boost/predef/architecture/x86/32.h
 *
 * | Predefined macro | Compiler 
 * | ---------------- | -------------------------------------------------------------
 * | i386 			  | Defined by GNU C
 * | __i386__		  | Defined by GNU C
 * | __i386__		  | Defined by GNU C
 * | __i486__		  | Defined by GNU C
 * | __i586__		  | Defined by GNU C
 * | __i686__		  | Defined by GNU C
 * | __i386 		  | Defined by Sun Studio
 * | __i386           | Defined by Stratus VOS C
 * | __IA32__ 		  | Defined by Stratus VOS C
 * | _M_I86           | Only defined for 16-bits architectures. Defined by Visual C++, Digital Mars, and Watcom C/C++ (see note below)
 * | _M_IX86          | Only defined for 32-bits architectures. Defined by Visual C++, Intel C/C++, Digital Mars, and Watcom C/C++
 * | __X86__          | Defined by Watcom C/C++
 * | _X86_            | Defined by MinGW32
 * | __THW_INTEL__    | Defined by XL C/C++
 * | __I86__          | Defined by Digital M ars
 * | __INTEL__        | Defined by CodeWarrior
 * | __386            | Defined by Diab
 * 
 **/
#if defined( i386 ) || defined( __i386 ) || defined( __i386__ ) || defined( __i486__ ) || defined( __i586__ ) || defined( __i686__ ) || defined( __IA32__ ) || defined( _M_I86 ) || defined( _M_IX86 ) || defined( __X86__ ) || defined( _X86_ ) || defined( __THW_INTEL__ ) || defined( __I86__ ) || defined( __INTEL__ ) || defined( __386 )
#    define MICRO_ARCH_x32
#endif

/**
 *    from:
 *        https://github.com/cpredef/predef/blob/master/Architectures.md
 *        https://github.com/boostorg/predef/blob/develop/include/boost/predef/architecture/x86/64.h
 *
 * | Predefined macro | Compiler 
 * | ---------------- | -------------------------------------------------------------
 * | __amd64__  	  | Defined by GNU C and Sun Studio
 * | __amd64 		  | Defined by GNU C and Sun Studio
 * | __x86_64__ 	  | Defined by GNU C and Sun Studio
 * | __x86_64__		  | Defined by GNU C and Sun Studio
 * | _M_X64			  | Defined by Visual C++
 * | _M_AMD64		  | Defined by Visual C++
 *
 **/
#if defined( __x86_64__ ) || defined( __x86_64 ) || defined( __amd64__ ) || defined( __amd64 ) || defined( _M_X64 ) || defined( _M_AMD64 )
#   define MICRO_ARCH_x64
#endif

/**
 *    from:
 *        https://github.com/boostorg/predef/blob/develop/include/boost/predef/architecture/arm.h
 *        https://github.com/cpredef/predef/blob/master/Architectures.md
 *        https://wiki.ubuntu.com/ARM/Thumb2PortingHowto
 * 
 * | Predefined macro	 | Compiler
 * | ------------------- | ----------------------------------------------------
 * | __arm__             | Defined by GNU C and RealView
 * | __thumb__           | Defined by GNU C and RealView in Thumb mode
 * | __TARGET_ARCH_ARM   | Defined by RealView
 * | __TARGET_ARCH_THUMB | Defined by RealView
 * | _ARM                | Defined by ImageCraft C
 * | _M_ARM              | Defined by Visual Studio
 * | _M_ARMT             | Defined by Visual Studio in Thumb mode
 * | __arm               | Defined by Diab
 *
 * | Model 	 | Predefined macro
 * | ------- | ---------------------------------------------------------------- 
 * | ARM 2   |   __ARM_ARCH_2__  
 * | ARM 3   |   __ARM_ARCH_3__, __ARM_ARCH_3M__
 * | ARM 4   |   __ARM_ARCH_4__
 * | ARM 4T  |   __ARM_ARCH_4T__, __TARGET_ARM_4T
 * | ARM 5   |   __ARM_ARCH_5__, __ARM_ARCH_5E__
 * | ARM 5T  |   __ARM_ARCH_5T__, __ARM_ARCH_5TE__, __ARM_ARCH_5TEJ__    
 * | ARM 6   |   __ARM_ARCH_6__, __ARM_ARCH_6J__, __ARM_ARCH_6K__, __ARM_ARCH_6Z__, __ARM_ARCH_6ZK__
 * | ARM 6T2 |   __ARM_ARCH_6T2__    
 * | ARM 7   |   __ARM_ARCH_7__, __ARM_ARCH_7A__, __ARM_ARCH_7R__, __ARM_ARCH_7M__, __ARM_ARCH_7S__
 * | ARM 2   |   __ARM_ARCH_2__  
 * | ARM 3   |   __ARM_ARCH_3__, __ARM_ARCH_3M__ 
 * | ARM 4T  |   __ARM_ARCH_4T__, __TARGET_ARM_4T
 * | ARM 5   |   __ARM_ARCH_5__, __ARM_ARCH_5E__
 * | ARM 5T  |   __ARM_ARCH_5T__,__ARM_ARCH_5TE__,__ARM_ARCH_5TEJ__  
 * | ARM 6   |   __ARM_ARCH_6__, __ARM_ARCH_6J__, __ARM_ARCH_6K__, __ARM_ARCH_6Z__, __ARM_ARCH_6ZK__
 * | ARM 6T2 |   __ARM_ARCH_6T2__    
 * | ARM 7   |   __ARM_ARCH_7__, __ARM_ARCH_7A__, __ARM_ARCH_7R__, __ARM_ARCH_7M__, __ARM_ARCH_7S__
 *
 **/
#if defined( __ARM_ARCH_2__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_2 
#elif defined( __ARM_ARCH_3__ ) || defined( __ARM_ARCH_3M__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_3 
#elif defined( __ARM_ARCH_4__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_4 
#elif defined( __ARM_ARCH_4T__ ) || defined( __TARGET_ARM_4T )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_4T 
#elif defined( __ARM_ARCH_5__ ) || defined( __ARM_ARCH_5E__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_5 
#elif defined( __ARM_ARCH_5T__ ) || defined( __ARM_ARCH_5TE__ ) || defined(__ARM_ARCH_5TEJ__)
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_5T 
#elif defined( __ARM_ARCH_6__ ) || defined( __ARM_ARCH_6J__ ) || defined( __ARM_ARCH_6K__ ) || defined( __ARM_ARCH_6Z__) || defined( __ARM_ARCH_6ZK__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_6 
#elif defined( __ARM_ARCH_6T2__ ) || defined( __ARM_ARCH_6T2__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_6T2 
#elif defined( __ARM_ARCH_7__ ) || defined( __ARM_ARCH_7A__ ) || defined( __ARM_ARCH_7R__ ) || defined( __ARM_ARCH_7M__ ) || defined( __ARM_ARCH_7S__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_7 
#elif defined( __ARM_ARCH_7A__ ) || defined( __ARM_ARCH_7R__ ) || defined( __ARM_ARCH_7M__ ) || defined( __ARM_ARCH_7S__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_7A 
#elif defined( __ARM_ARCH_7R__ ) || defined( __ARM_ARCH_7M__ ) || defined( __ARM_ARCH_7S__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_7R 
#elif defined( __ARM_ARCH_7M__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_7M 
#elif defined( __ARM_ARCH_7S__ )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_7S 
#elif defined( __aarch64__ ) || defined( _M_ARM64 ) || defined( __AARCH64EL__ ) || defined( __arm64 )
#   define MICRO_ARCH_ARM 
#   define MICRO_ARCH_ARM_64 
#elif defined( __arm__ ) || defined( __thumb__ ) || defined( __TARGET_ARCH_ARM ) || defined( __TARGET_ARCH_THUMB ) || defined( __ARM ) || defined( _M_ARM ) || defined( _M_ARM_T ) || defined( __ARM_ARCH )
#   define MICRO_ARCH_ARM 
#endif

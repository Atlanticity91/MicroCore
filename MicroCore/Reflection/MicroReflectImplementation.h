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

#include "Storage/MicroReflectStorageClass.h"

namespace micro {

	/**
	 * ReflectTypeTag template struct
	 * @note : Define Type tag for template dispatch.
	 **/
	template<class T>
	struct ReflectTypeTag { };

	/**
	 * GetTypeImpl function
	 * @note : Get type implementation detail.
	 * @template T : Type to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectType* GetTypeImpl( ReflectTypeTag<T> ) noexcept {
		return nullptr;
	};

	/**
	 * ReflectClassTag template struct
	 * @note : Define class tag for template dispatch.
	 **/
	template<class T>
	struct ReflectClassTag { };

	/**
	 * GetClassImpl function
	 * @note : Get class implementation detail.
	 * @template T : Type of class to process.
	 * @return : Return pointer to the type structure detail.
	 **/
	template<class T>
	const ReflectClass* GetClassImpl( ReflectClassTag<T> ) {
		return nullptr;
	};

};

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

#include "../../Yaml/MicroYamlWriter.h"

micro_class MicroWork {

public:
	using Task_t = MicroCallable<bool, const uint32_t, void*>;
	using Callback_t = MicroCallable<void, const uint32_t, void*>;

private:
	uint32_t m_uuid;
	void* m_user_data;
	Task_t m_task;
	Callback_t m_on_error;
	Callback_t m_on_success;

public:
	MicroWork( );

	MicroWork(
		const uint32_t uuid,
		const Task_t& task,
		const Callback_t& on_error,
		const Callback_t& on_success,
		void* user_data
	);

	void Execute( );

public:
	bool GetIsValid( ) const;

public:
	operator bool( ) const;

	MicroWork& operator=( const MicroWork& other );

};

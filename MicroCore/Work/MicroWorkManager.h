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

#include "Workers/MicroWorkerManager.h"

/**
 * MicroWorkManager class
 * @note : Represent work manager for multithreading.
 **/
micro_class MicroWorkManager {

private:
	MicroWorkSignal<bool> m_signal;
	MicroWorkQueue<256> m_queue;
	MicroWorkerManager m_workers;

public:
	MicroWorkManager( );

	~MicroWorkManager( );

	bool Create( const MicroWorkSpecification& specification, void* init_data );

	inline void Enqueue(
		const uint32_t work_uuid,
		const MicroWork::Task_t& task
	);

	inline void Enqueue(
		const uint32_t work_uuid,
		const MicroWork::Task_t& task,
		void* user_data
	);

	inline void Enqueue(
		const uint32_t work_uuid,
		const MicroWork::Task_t& task,
		const MicroWork::Callback_t& error,
		const MicroWork::Callback_t& success
	);

	void Enqueue(
		const uint32_t work_uuid,
		const MicroWork::Task_t& task,
		const MicroWork::Callback_t& error,
		const MicroWork::Callback_t& success,
		void* user_data
	);

	void Terminate( );

public:
	template<typename Task>
	void Enqueue( const uint32_t work_uuid, Task&& task ) {
		Enqueue( work_uuid, MicroWork::Task_t{ std::forward<Task>( task ) }, { }, { }, nullptr );
	};

	template<typename Task>
	void Enqueue( const uint32_t work_uuid, Task&& task, void* user_data ) {
		Enqueue( work_uuid, MicroWork::Task_t{ std::forward<Task>( task ) }, { }, { }, user_data );
	};

	template<typename Task, typename OnError, typename OnSuccess>
	void Enqueue(
		const uint32_t work_uuid,
		Task&& task,
		OnError&& on_error,
		OnSuccess&& on_success
	) {
		Enqueue(
			work_uuid,
			MicroWork::Task_t{ std::forward<Task>( task ) },
			MicroWork::Callback_t{ std::forward<OnError>( on_error ) },
			MicroWork::Callback_t{ std::forward<OnSuccess>( on_success ) },
			nullptr
		);
	};

	template<typename Task, typename OnError, typename OnSuccess>
	void Enqueue(
		const uint32_t work_uuid,
		Task&& task,
		OnError&& on_error,
		OnSuccess&& on_success,
		void* user_data
	) {
		Enqueue(
			work_uuid,
			MicroWork::Task_t{ std::forward<Task>( task ) },
			MicroWork::Callback_t{ std::forward<OnError>( on_error ) },
			MicroWork::Callback_t{ std::forward<OnSuccess>( on_success ) },
			user_data
		);
	};

public:
	uint32_t GetWorkCount( ) const;

	uint32_t GetWorkerCount( ) const;

};

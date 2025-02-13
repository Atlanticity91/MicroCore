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

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroWorkManager::MicroWorkManager( )
	: m_signal{ false },
	m_queue{ },
	m_workers{ } 
{ }

MicroWorkManager::~MicroWorkManager( ) {
	Terminate( );
}

bool MicroWorkManager::Create( 
	const MicroWorkSpecification& specification, 
	void* init_data 
) {
	auto lambda = [ this, specification ]( void* init_data ) {
		specification.CreateCallback.Invoke( std::move( init_data ) );

		auto id = std::this_thread::get_id( );

		while ( true ) {
			auto thread_work = MicroWork{ };
			auto guard_lock = std::unique_lock{ m_signal.m_mutex };

			m_signal.m_condition.wait( guard_lock, [ this ]( ) {
				return m_signal.m_value.load( std::memory_order_relaxed ) || !m_queue.GetIsEmpty( );
			} );

			if ( m_signal.m_value.load( std::memory_order_relaxed ) ) {
				specification.TerminateCallback.Invoke( );

				return;
			}

			if ( m_queue.Dequeue( m_signal.m_condition, thread_work ) ) {
				guard_lock.unlock( );
				thread_work.Execute( );
			}
		}
	};

	return m_workers.Create( lambda, init_data );
}

void MicroWorkManager::Enqueue(
	const uint32_t work_uuid,
	const MicroWork::Task_t& task
) {
	Enqueue( work_uuid, task, { }, { }, nullptr );
}

void MicroWorkManager::Enqueue(
	const uint32_t work_uuid,
	const MicroWork::Task_t& task,
	void* user_data
) {
	Enqueue( work_uuid, task, { }, { }, user_data );
}

void MicroWorkManager::Enqueue(
	const uint32_t work_uuid,
	const MicroWork::Task_t& task,
	const MicroWork::Callback_t& error,
	const MicroWork::Callback_t& success
) {
	Enqueue( work_uuid, task, error, success, nullptr );
}

void MicroWorkManager::Enqueue(
	const uint32_t work_uuid,
	const MicroWork::Task_t& task,
	const MicroWork::Callback_t& error,
	const MicroWork::Callback_t& success,
	void* user_data
) {
	if ( task )
		m_queue.Enqueue( m_signal.m_condition, { work_uuid, task, error, success, user_data } );
}

void MicroWorkManager::Terminate( ) {
	m_signal.Send( );
	m_workers.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
uint32_t MicroWorkManager::GetWorkCount( ) const {
	return m_queue.GetCount( );
}

uint32_t MicroWorkManager::GetWorkerCount( ) const {
	return m_workers.GetCount( );
}

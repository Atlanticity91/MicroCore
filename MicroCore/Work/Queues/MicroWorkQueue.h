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

#include "MicroWork.h"

#pragma once

template<uint32_t Capacity>
	requires ( Capacity > 1 )
class MicroWorkQueue final {

private:
	uint32_t m_tail;
	uint32_t m_head;
	mutable std::mutex m_queue_lock;
	std::condition_variable m_queue_wait;
	std::array<MicroWork, Capacity> m_work_list;
	std::array<uint32_t, Capacity> m_work_queue;

public:
	MicroWorkQueue( )
		: m_tail{ 0 },
		m_head{ 0 },
		m_queue_lock{ },
		m_queue_wait{ },
		m_work_list{ },
		m_work_queue{ } 
	{ };

	~MicroWorkQueue( ) = default;

	void Enqueue( std::condition_variable& worker_wait, const MicroWork& work ) {
		if ( !work.GetIsValid( ) )
			return;

		{
			auto queue_lock = std::unique_lock{ m_queue_lock };
			auto next_index = ( m_head + 1 ) % Capacity;

			while ( next_index == m_tail )
				m_queue_wait.wait( queue_lock );

			m_work_list[ m_head ] = work;
			m_head = next_index;
		}

		worker_wait.notify_one( );
	};

	bool Dequeue( std::condition_variable& worker_wait, MicroWork& work ) {
		auto result = false;

		{
			auto lock_guard = std::unique_lock{ m_queue_lock };
			auto next_index = ( m_tail + 1 ) % Capacity;

			if ( result = ( m_head != m_tail ) ) {
				work = m_work_list[ m_tail ];
				m_tail = next_index;
			}
		}

		m_queue_wait.notify_one( );

		return result;
	};

public:
	bool GetIsEmpty( ) const {
		auto lock_guard = std::unique_lock{ m_queue_lock };

		return m_head == m_tail;
	};

	uint32_t GetHead( ) const {
		auto lock_guard = std::unique_lock{ m_queue_lock };

		return m_head;
	};

	uint32_t GetTail( ) const {
		auto lock_guard = std::unique_lock{ m_queue_lock };

		return m_tail;
	};

	uint32_t GetCount( ) const {
		auto lock_guard = std::unique_lock{ m_queue_lock };

		return ( m_head >= m_tail ) ? ( m_head - m_tail ) : ( Capacity - ( m_tail - m_head ) );
	};

};

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

#include <__micro_core_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroWorkManager::MicroWorkManager( )
	: m_works{ },
	m_workers{ },
	m_can_work{ true }
{ }

bool MicroWorkManager::Create( ) {
	auto thread_id = std::thread::hardware_concurrency( ) / 2;

	m_workers.resize( thread_id );

	while ( thread_id-- > 0 ) {
		auto thread = std::thread( WorkExecution, this );

		m_workers[ thread_id ] = std::move( thread );
	}

	return m_workers.size( ) > 0;
}

void MicroWorkManager::PushWork( MicroWorkPriorities priority, const MicroWork& work ) {
	if ( work.GetIsValid( ) )
		m_works[ (uint32_t)priority ].push( work );
}

void MicroWorkManager::Destroy( ) {
	m_mutex.lock( );
	m_can_work = false;
	m_mutex.unlock( );

	for ( auto& worker : m_workers )
		worker.join( );
}

void MicroWorkManager::WorkExecution( MicroWorkManager* work_manager ) {
	auto work = MicroWork{ };

	while ( work_manager->GetCanWork( ) ) {
		if ( work_manager->PopWork( work ) ) {
			if ( std::invoke( work.Execute, work_manager, work.Storage ) ) {
				if ( work.OnSucced )
					std::invoke( work.OnSucced, work_manager, work.Storage );
			} else {
				if ( work.OnFailed )
					std::invoke( work.OnFailed, work_manager, work.Storage );
			}
		} else
			std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroWorkManager::GetCanWork( ) {
	auto can_work = false;

	m_mutex.lock( );
	can_work = m_can_work;
	m_mutex.unlock( );

	return can_work;
}

uint32_t MicroWorkManager::GetCount( ) const {
	return (uint32_t)m_workers.size( );
}

bool MicroWorkManager::PopWork( MicroWork& work ) {
	auto has_work = false;
	auto work_id  = (uint32_t)MicroWorkPriorities::MW_PRIORITY_COUNT;
	
	m_mutex.lock( );

	while ( !has_work && work_id-- > 0 ) {
		if ( m_works[ work_id ].size( ) > 0 ) {
			work = m_works[ work_id ].front( );

			m_works[ work_id ].pop( );

			has_work = true;
		}
	}

	m_mutex.unlock( );

	return has_work;
}

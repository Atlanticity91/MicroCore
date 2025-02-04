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
MicroWorkerManager::MicroWorkerManager( )
	: m_workers{ } 
{ }

bool MicroWorkerManager::Create( 
	std::function<void( void* )> thread_runner, 
	void* init_data 
) {
	auto thread_count = std::thread::hardware_concurrency( );
	auto result		  = ( thread_count > 2 );

	if ( result ) {
		thread_count -= 2;

		m_workers.resize( thread_count );

		while ( thread_count-- > 0 )
			m_workers[ thread_count ] = std::move( std::thread{ thread_runner, init_data } );
	}

	return result;
}

void MicroWorkerManager::Terminate( ) {
	for ( auto& worker : m_workers ) {
		if ( worker.joinable( ) )
			worker.join( );
	}

	m_workers.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
uint32_t MicroWorkerManager::GetCount( ) const {
	return (uint32_t)m_workers.size( );
}

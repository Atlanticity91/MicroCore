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
MicroWork::MicroWork( )
	: MicroWork{ 0, { }, { }, { }, nullptr } 
{ }

MicroWork::MicroWork(
	const uint32_t uuid,
	const Task_t& task,
	const Callback_t& on_error,
	const Callback_t& on_success,
	void* user_data
)
	: m_uuid{ uuid },
	m_user_data{ user_data },
	m_task{ task },
	m_on_error{ on_error },
	m_on_success{ on_success } 
{ }

void MicroWork::Execute( ) {
	try {
		if ( m_task.Invoke( std::move( m_uuid ), std::move( m_user_data ) ) ) {
			if ( m_on_success )
				m_on_success.Invoke( std::move( m_uuid ), std::move( m_user_data ) );
		} else if ( m_on_error )
			m_on_error.Invoke( std::move( m_uuid ), std::move( m_user_data ) );
	} catch ( const std::exception& exception ) {
		auto* message = exception.what( );

		micro::log_errr( "%s\n", message );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroWork::GetIsValid( ) const {
	return (bool)m_task;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroWork::operator bool( ) const {
	return GetIsValid( );
}

MicroWork& MicroWork::operator=( const MicroWork& other ) {
	m_uuid		 = other.m_uuid;
	m_user_data  = other.m_user_data;
	m_task		 = other.m_task;
	m_on_error   = other.m_on_error;
	m_on_success = other.m_on_success;

	return micro_self;
}

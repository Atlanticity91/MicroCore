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

#include <__micro_core_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroFileVirtual::MicroFileVirtual( )
	: MicroFile{ },
	m_pointer{ nullptr },
	m_cursor{ 0 },
	m_length{ 0 }
{ }

MicroFileVirtual::MicroFileVirtual(
	const void* data,
	const uint32_t length,
	const MicroFileAccessors accessor,
	const MicroFileTypes type
)
	: MicroFileVirtual{ }
{
	Open( data, length, accessor, type );
}

MicroFileVirtual::MicroFileVirtual( MicroFileVirtual&& other ) noexcept
	: MicroFileVirtual{ }
{
	micro::move( other, micro_self );

	other.m_type	 = MicroFileTypes::Undefined;
	other.m_accessor = MicroFileAccessors::None;
	other.m_pointer  = nullptr;
	other.m_cursor   = 0;
	other.m_length   = 0;
}

bool MicroFileVirtual::Open(
	const void* data,
	const uint32_t length,
	const MicroFileAccessors accessor,
	const MicroFileTypes type
) {
	auto result = false;

	if ( data != nullptr && length > 0 ) {
		m_pointer = micro_cast( data, uint8_t* );
		m_length  = length;
	}

	return result;
}

void MicroFileVirtual::Seek( const uint32_t offset ) {
	if ( ( m_length - m_cursor ) <= offset )
		m_cursor += offset;
	else
		SeekEnd( );
}

void MicroFileVirtual::SeekBegin( ) {
	m_cursor = 0;
}

void MicroFileVirtual::SeekEnd( ) {
	m_cursor = m_length;
}

uint32_t MicroFileVirtual::Read( const uint32_t length, uint8_t* buffer ) {
	auto result = (uint32_t)0;

	if ( GetCanRead( ) && !GetIsEOF( ) ) {
		auto query_length = ( m_length - m_cursor );

		if ( length < query_length )
			query_length = length;

		micro::move( query_length, micro_cast( m_pointer + m_cursor, const void* ), micro_cast( buffer, void* ) );

		m_cursor += query_length;
	}

	return result;
}

uint32_t MicroFileVirtual::Write(
	const uint32_t length,
	const uint8_t* buffer
) {
	auto result = (uint32_t)0;

	if ( GetCanWrite( ) && !GetIsEOF( ) ) {
		auto query_length = ( m_length - m_cursor );

		if ( length < query_length )
			query_length = length;

		micro::move( query_length, micro_cast( buffer, const void* ), micro_cast( m_pointer + m_cursor, void* ) );

		m_cursor += query_length;
	}

	return result;
}

void MicroFileVirtual::Close( ) {
	if ( GetIsValid( ) ) {
		MicroFile::Close( );

		m_pointer = nullptr;
		m_cursor  = 0;
		m_length  = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroFileVirtual::GetIsValid( ) const {
	return MicroFile::GetIsValid( ) && ( m_pointer != nullptr ) && ( m_length > 0 );
}

uint32_t MicroFileVirtual::GetSize( ) const {
	return m_length;
}

uint8_t* MicroFileVirtual::GetNative( ) const {
	return m_pointer;
}

uint32_t MicroFileVirtual::GetCursor( ) const {
	return m_cursor;
}

bool MicroFileVirtual::GetIsEOF( ) const {
	return ( m_cursor == m_length );
}

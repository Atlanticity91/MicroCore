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
MicroFile::MicroFile( )
	: m_accessor{ MicroFileAccessors::MFA_NONE },
	m_handle{ nullptr } 
{ }

bool MicroFile::Open( const std::string path, const MicroFileAccessors accessor ) {
	auto* path_ = path.c_str( );
	
	return Open( path_, accessor );
}

bool MicroFile::Open( micro_string path, const MicroFileAccessors accessor ) {
	auto file_mode = GetFileMode( accessor );

	m_accessor = accessor;

#	ifdef _WIN64
	return accessor > MicroFileAccessors::MFA_NONE && fopen_s( &m_handle, path, file_mode ) == 0;
#	else
	if ( accessor > MicroFileAccessors::MFA_NONE )
		m_handle = fopen( path, file_mode );

	return m_handle != nullptr;
#	endif
}

void MicroFile::Seek( const uint32_t offset ) {
	if ( GetIsValid( ) )
		fseek( m_handle, offset, SEEK_CUR );
}

void MicroFile::SeekBegin( ) {
	if ( GetIsValid( ) )
		fseek( m_handle, 0, SEEK_SET );
}

void MicroFile::SeekEnd( ) {
	if ( GetIsValid( ) )
		fseek( m_handle, 0, SEEK_END );
}

uint32_t MicroFile::Read( const uint32_t length, void* buffer ) {
	micro_assert( length > 0, "You can't read data form file with a 0 length buffer." );
	micro_assert( buffer != nullptr, "You can't read from file to an invalid buffer." );

	auto count = (uint32_t)0;

	if ( GetCanRead( ) ) {
#		ifdef _WIN64
		count = (uint32_t)fread_s( buffer, length, sizeof( uint8_t ), length, m_handle );
#		else
#		endif
	}

	return count;
}

uint32_t MicroFile::Write( const uint32_t length, const void* buffer ) {
	micro_assert( length > 0, "You can't write data to file with a 0 length buffer." );
	micro_assert( buffer != nullptr, "You can't write to file with an invalid buffer." );

	auto count = (uint32_t)0;
	
	if ( GetCanWrite( ) )
		count = (uint32_t)fwrite( buffer, sizeof( uint8_t ), length, m_handle );

	return count;
}

void MicroFile::Close( ) {
	if ( GetIsValid( ) ) {
		fclose( m_handle );

		m_handle = nullptr;
	}

	m_accessor = MicroFileAccessors::MFA_NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroFile::GetIsValid( ) const {
	return m_accessor > MicroFileAccessors::MFA_NONE && m_handle != nullptr;
}

FILE* MicroFile::GetNative( ) const {
	return m_handle;
}

MicroFileAccessors MicroFile::GetAccessor( ) const {
	return m_accessor;
}

uint32_t MicroFile::GetSize( ) const {
	auto size = (uint32_t)0;

	if ( GetCanRead( ) ) {
		auto cursor = ftell( m_handle );

		fseek( m_handle, 0, SEEK_END );

		size = (uint32_t)ftell( m_handle );

		fseek( m_handle, cursor, SEEK_SET );
	}

	return size;
}

bool MicroFile::GetCanRead( ) const {
	return GetIsValid( ) && ( (uint32_t)m_accessor & (uint32_t)MicroFileAccessors::MFA_READ );
}

bool MicroFile::GetCanWrite( ) const {
	return GetIsValid( ) && ( (uint32_t)m_accessor & (uint32_t)MicroFileAccessors::MFA_WRITE );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
micro_string MicroFile::GetFileMode( const MicroFileAccessors accessor ) const {
	auto file_mode = "";

	switch ( accessor ) {
		case MicroFileAccessors::MFA_READ   : file_mode = "r"; break;
		case MicroFileAccessors::MFA_WRITE  : file_mode = "w"; break;
		case MicroFileAccessors::MFA_APPEND : file_mode = "a"; break;

		case MicroFileAccessors::MFA_BINARY_READ   : file_mode = "rb"; break;
		case MicroFileAccessors::MFA_BINARY_WRITE  : file_mode = "wb"; break;
		case MicroFileAccessors::MFA_BINARY_APPEND : file_mode = "ab"; break;

		default: break;
	}

	return file_mode;
}

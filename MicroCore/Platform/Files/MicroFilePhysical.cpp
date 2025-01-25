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
MicroFilePhysical::MicroFilePhysical( ) 
	: MicroFile{ },
	m_handle{ NULL }
{ }

MicroFilePhysical::MicroFilePhysical(
	const std::string& path,
	const MicroFileAccessors accessor,
	const MicroFileTypes type
)
	: MicroFilePhysical{ }
{
	Open( path, accessor, type );
}

MicroFilePhysical::MicroFilePhysical( MicroFilePhysical&& other ) noexcept
	: MicroFilePhysical{ }
{
	micro::move( other, micro_self );
	
	other.m_type	 = MicroFileTypes::Undefined;
	other.m_accessor = MicroFileAccessors::None;
	other.m_handle   = NULL;
}

bool MicroFilePhysical::Open(
	const std::string& path,
	const MicroFileAccessors accessor,
	const MicroFileTypes type
) {
	if ( accessor > MicroFileAccessors::None && type > MicroFileTypes::Undefined ) {
		auto* file_path = path.c_str( );
		auto file_mode = GetFileMode( accessor );

		m_accessor = accessor;
		m_type = type;
		m_handle = micro::file_open( file_path, file_mode );
	}

	return GetIsValid( );
}

void MicroFilePhysical::Seek( const uint32_t offset ) {
	if ( GetIsValid( ) )
		micro::file_seek( m_handle, SEEK_CUR, offset );
}

void MicroFilePhysical::SeekBegin( ) {
	if ( GetIsValid( ) )
		micro::file_seek( m_handle, SEEK_SET, 0 );
}

void MicroFilePhysical::SeekEnd( ) {
	if ( GetIsValid( ) )
		micro::file_seek( m_handle, SEEK_END, 0 );
}

uint32_t MicroFilePhysical::Read( const uint32_t length, uint8_t* buffer ) {
	micro_assert( length > 0, "You can't read data form file with a 0 length buffer." );
	micro_assert( buffer != nullptr, "You can't read from file to an invalid buffer." );

	auto count = (uint32_t)0;

	if ( GetCanRead( ) && !GetIsEOF( ) )
		count = micro::file_read( m_handle, length, buffer );

	return count;
}

uint32_t MicroFilePhysical::Write( const uint32_t length, const uint8_t* buffer ) {
	micro_assert( length > 0, "You can't write data to file with a 0 length buffer." );
	micro_assert( buffer != nullptr, "You can't write to file with an invalid buffer." );

	auto count = (uint32_t)0;

	if ( GetCanWrite( ) )
		count = micro::file_write( m_handle, length, buffer );

	return count;
}

void MicroFilePhysical::Close( ) {
	if ( GetIsValid( ) ) {
		MicroFile::Close( );

		micro::file_close( m_handle );
	}

	m_accessor = MicroFileAccessors::None;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroFilePhysical::GetIsValid( ) const {
	return MicroFile::GetIsValid( ) && ( m_handle != NULL );
}

uint32_t MicroFilePhysical::GetSize( ) const {
	auto result = (uint32_t)0;

	if ( GetCanRead( ) ) {
		result = micro::file_seek( m_handle, SEEK_END, 0 );
		result = micro::file_seek( m_handle, SEEK_SET, result );
	}

	return result;
}
uint32_t MicroFilePhysical::GetCursor( ) const {
	auto result = (uint32_t)0;

	if ( GetIsValid( ) )
		result = micro::file_tell( m_handle );

	return result;
}

bool MicroFilePhysical::GetIsEOF( ) const {
	auto result = true;

	if ( GetIsValid( ) )
		result = micro::file_is_eof( m_handle );

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
micro_string MicroFilePhysical::GetFileMode( const MicroFileAccessors accessor ) const {
	auto file_mode = "";

	switch ( accessor ) {
		case MicroFileAccessors::Read  : file_mode = ( m_type == MicroFileTypes::Text ) ? "r"  : "rb";  break;
		case MicroFileAccessors::Write : file_mode = ( m_type == MicroFileTypes::Text ) ? "w"  : "wb";  break;
		case MicroFileAccessors::Edit  : file_mode = ( m_type == MicroFileTypes::Text ) ? "a+" : "ab+"; break;

		default: break;
	}

	return file_mode;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroFilePhysical::operator FILE* ( ) {
	return GetNative( );
}

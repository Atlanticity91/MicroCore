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
namespace micro {

	bool is_little_endian( ) {
		static uint32_t test = 1;

		return micro_ref( micro_ptr_as( test, int8_t* ) ) == 1;
	}

	std::string cast_thread_id( const std::thread::id& thread_id ) {
		auto stream = std::ostringstream{ };

		stream << thread_id;

		return stream.str( );
	}

	bool copy( const uint32_t length, const void* src, void* dst ) {
		micro_assert( length > 0, "You can't copy data form buffer to buffer with a 0 size buffer." );
		micro_assert( src != nullptr, "You can't copy data from a null buffer." );
		micro_assert( dst != nullptr, "You can't copy data to a null buffer." );

	#	ifdef _WIN64
		return memcpy_s( dst, length, src, length ) == 0;
	#	else
		return memcpy( dst, src, length ) == dst;
	#	endif
	}


	bool move( const uint32_t length, const void* src, void* dst ) {
		micro_assert( length > 0, "You can't move data form buffer to buffer with a 0 size buffer." );
		micro_assert( src != nullptr, "You can't move data from a null buffer." );
		micro_assert( dst != nullptr, "You can't move data to a null buffer." );

	#	ifdef _WIN64
		return memmove_s( dst, length, src, length ) == 0;
	#	else
		return memmove( dst, src, length ) == dst;
	#	endif
	}

	FILE* file_open( micro_string path, micro_string mode ) {
		auto file = micro_cast( NULL, FILE* );

	#	ifdef _WIN64
		fopen_s( micro_ptr( file ), path, mode );
	#	else
		file = fopen( path, mode );
	#	endif

		return file;
	}

	uint32_t file_read( FILE*& file, const uint32_t length, uint8_t* buffer ) {
		auto count = (uint32_t)0;

		if ( file != NULL ) {
	#		ifdef _WIN64
			count = (uint32_t)fread_s( buffer, length, sizeof( uint8_t ), length, file );
	#		else
			count = (uint32_t)fread( buffer, sizeof( uint8_t ), length, file );
	#		endif
		}

		return count;
	}

	uint32_t file_write( FILE*& file, const uint32_t length, const uint8_t* buffer ) {
		return (uint32_t)fwrite( micro_cast( buffer, const void* ), sizeof( uint8_t ), length, file );
	}

	void file_close( FILE*& file ) {
		fclose( file );

		file = NULL;
	}

	uint32_t file_seek( FILE* file, const uint32_t origin, const uint32_t offset ) {
		auto result = file_tell( file );

		fseek( file, offset, origin );

		return result;
	}

	uint32_t file_tell( FILE* file ) {
		return (uint32_t)ftell( file );
	}

	bool file_is_eof( FILE* file ) {
		return ( feof( file ) != 0 );
	}

};

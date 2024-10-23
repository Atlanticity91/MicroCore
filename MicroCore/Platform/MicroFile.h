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

#pragma once

#include "MicroAssert.h"

/**
 * MicroFileAccessors enum class
 * @note : Defined all accessor for file access.
 **/
enum class MicroFileAccessors : uint32_t {

	None  = 0,
	Read  = 1 << 0,
	Write = 1 << 1,
	Edit  = Read | Write

};

/**
 * MicroFileTypes enum class
 * @note : Defined all possible file types.
 **/
enum class MicroFileTypes : uint32_t { 

	Undefined = 0,
	Text,
	Binary 

};

/**
 * MicroFile final class
 * @note : Represent file, replace FILE*.
 **/
class MicroFile final {

private:
	MicroFileTypes m_type;
	MicroFileAccessors m_accessor;
	FILE* m_handle;

public:
	/**
	 * Constructor
	 **/
	MicroFile( );

	/**
	 * Destructor
	 **/
	~MicroFile( ) = default;

	/**
	 * Open function
	 * @note : Open file specified by the path.
	 * @param path : Path with extension to the query file.
	 * @param mode : File opening mode, actualy same as native c fopen.
	 * @param type : Query file type.
	 * @return : True for succes.
	 **/
	bool Open( 
		const std::string path,
		const MicroFileAccessors accessor,
		const MicroFileTypes type 
	);

	/**
	 * Open function
	 * @note : Open file specified by the path.
	 * @param path : Path with extension to the query file.
	 * @param accessor : File opening mode, actualy same as native c fopen.
	 * @param type : Query file type.
	 * @return : True for succes.
	 **/
	bool Open( 
		micro_string path,
		const MicroFileAccessors accessor,
		const MicroFileTypes type
	);

	/**
	 * Seek procedure
	 * @note : Seek from current file position.
	 * @param offset : Offset in byte count.
	 **/
	void Seek( const uint32_t offset );

	/**
	 * SeekBegin procedure
	 * @note : Seek to begin of the file.
	 **/
	void SeekBegin( );

	/**
	 * SeekEnd procedure
	 * @note : Seek to end of the file.
	 **/
	void SeekEnd( );
	
	/**
	 * Read function
	 * @note : Read data from current file.
	 * @param length : Length of the buffer to store readed data.
	 * @param buffer : Pointer to the buffer to store readed data.
	 * @return : Count of bytes loaded to the buffer
	 **/
	uint32_t Read( const uint32_t length, void* buffer );

	/**
	 * Read function
	 * @note : Write data to current file.
	 * @param length : Length of the buffer to write.
	 * @param buffer : Pointer to the buffer to write.
	 * @return : Count of bytes writed to the file
	 **/
	uint32_t Write( const uint32_t length, const void* buffer );

	/**
	 * Close procedure
	 * @note : Close current file.
	 **/
	void Close( );

public:
	/**
	 * Read template function
	 * @note : Read data from file.
	 * @template Type : Type of the data to read.
	 * @param data : Reference to the variable used to store the read data.
	 * @return : Count of bytes loaded from file.
	 **/
	template<typename Type>
	uint32_t Read( Type& data ) {
		auto* buffer = (const void*)&data;
		auto length  = (uint32_t)sizeof( Type );

		return Read( length, buffer );
	};

	/**
	 * Read template function
	 * @note : Read vector from file.
	 * @template Type : Type of the vector data to read.
	 * @param data : Reference to the vector used to store the read data.
	 * @return : Count of bytes loaded from file.
	 **/
	template<typename Type>
	uint32_t Read( std::vector<Type>& data ) {
		auto length = (uint32_t)0;

		Read( length );

		data.resize( (size_t)length );

		auto* buffer = data.data( );

		return Read( length * (uint32_t)sizeof( Type ), buffer );
	};

	/**
	 * Write template function
	 * @note : Write data to file.
	 * @template Type : Type of the data to write.
	 * @param data : Reference to the variable used to store data to write.
	 * @return : Count of bytes writed to the file.
	 **/
	template<typename Type>
	uint32_t Write( const Type& data ) {
		auto* buffer = data.data( );
		auto length  = (uint32_t)data.size( );

		return Write( length, buffer );
	};

	/**
	 * Write template function
	 * @note : Write vector to file.
	 * @template Type : Type of the vector data to write.
	 * @param data : Reference to the vector used to store data to write.
	 * @return : Count of bytes writed to the file.
	 **/
	template<typename Type>
	uint32_t Write( const std::vector<Type>& data ) {
		auto* buffer = data.data( );
		auto length  = (uint32_t)data.size( );

		Write( length );

		return Write( length * (uint32_t)sizeof( Type ), buffer );
	};

public:
	/**
	 * GetIsValid const function
	 * @note : Get if the file is valid.
	 * @return : True for succes.
	 **/
	bool GetIsValid( ) const;

	/**
	 * GetNative const function
	 * @note : Get the FILE* handle.
	 **/
	FILE* GetNative( ) const;

	/**
	 * GetType const function
	 * @note : Get currrent file type.
	 **/
	MicroFileTypes GetType( ) const;

	/**
	 *  GetAccessor const function
	 * @note : Get current file accessor.
	 **/
	MicroFileAccessors GetAccessor( ) const;

	/**
	 * GetSize const function
	 * @note : Get current file size.
	 **/
	uint32_t GetSize( ) const;

	/**
	 * GetCanRead const function
	 * @note : Get if the file as read access.
	 **/
	bool GetCanRead( ) const;

	/**
	 *  GetCanWrite const function
	 * @note : Get if the file as write access.
	 **/
	bool GetCanWrite( ) const;

public:
	/**
	 * >> operator
	 * @note : C++ stream read style operator.
	 * @template Type : Type of data to read.
	 * @param data : Reference to the variable used to store readed data.
	 * @return : Count of bytes loaded from file.
	 **/
	template<typename Type>
	MicroFile& operator>>( Type& data ) {
		Read<Type>( data );

		return *this;
	};

	/**
	 * << operator
	 * @note : C++ stream write style operator.
	 * @template Type : Type of the data to write.
	 * @param data : Reference to the data to write.
	 * @return : Count of bytes writed to the file.
	 **/
	template<typename Type>
	MicroFile& operator<<( const Type& data ) {
		Write<Type>( data );

		return *this;
	};

private:
	/**
	 * GetFileMode const function
	 * @note : Convert file accessor to native file open mode.
	 * @param accessor : Query accessor to convert.
	 * @return : Native file open string.
	 **/
	micro_string GetFileMode( const MicroFileAccessors accessor ) const;

};

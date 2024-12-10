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

#include "MicroFileTypes.h"

/**
 * MicroFile final class
 * @note : Represent file, replace FILE*.
 **/
micro_class MicroFile {

protected:
	MicroFileTypes m_type;
	MicroFileAccessors m_accessor;

public:
	/**
	 * Constructor
	 **/
	MicroFile( );

	/**
	 * Destructor
	 **/
	~MicroFile( );

	/**
	 * Seek procedure
	 * @note : Seek from current file position.
	 * @param offset : Offset in byte count.
	 **/
	virtual void Seek( const uint32_t offset ) = 0;

	/**
	 * SeekBegin procedure
	 * @note : Seek to begin of the file.
	 **/
	virtual void SeekBegin( ) = 0;

	/**
	 * SeekEnd procedure
	 * @note : Seek to end of the file.
	 **/
	virtual void SeekEnd( ) = 0;
	
	/**
	 * Read function
	 * @note : Read data from current file.
	 * @param length : Length of the buffer to store readed data.
	 * @param buffer : Pointer to the buffer to store readed data.
	 * @return : Count of bytes loaded to the buffer
	 **/
	virtual uint32_t Read( const uint32_t length, uint8_t* buffer ) = 0;

	/**
	 * Read function
	 * @note : Write data to current file.
	 * @param length : Length of the buffer to write.
	 * @param buffer : Pointer to the buffer to write.
	 * @return : Count of bytes writed to the file
	 **/
	virtual uint32_t Write( const uint32_t length, const uint8_t* buffer ) = 0;

	/**
	 * Close procedure
	 * @note : Close current file.
	 **/
	virtual void Close( );

public:
	/**
	 * Read template function
	 * @note : Read data from file.
	 * @template Type : Type of the data to read.
	 * @param data : Reference to the variable used to store the read data.
	 * @return : Count of bytes loaded from file.
	 **/
	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	uint32_t Read( Type& data ) {
		auto* buffer = micro_ptr_as( data, uint8_t* );

		return Read( micro_sizeof( Type ), buffer );
	};

	/**
	 * Read template function
	 * @note : Read string from file.
	 * @param data : Query string storage.
	 * @return : Count of bytes loaded from file.
	 **/
	template<>
	uint32_t Read( std::string& data ) {
		auto length = (uint32_t)0;

		Read( length );

		data.resize( (size_t)length );

		auto* buffer = micro_cast( data.data( ), uint8_t* );

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
		requires ( !std::is_pointer<Type>::value )
	uint32_t Read( std::vector<Type>& data ) {
		auto length = (uint32_t)0;

		Read( length );

		data.resize( (size_t)length );

		auto* buffer = micro_cast( data.data( ), uint8_t* );

		return Read( length * micro_sizeof( Type ), buffer );
	};

	/**
	 * Write template function
	 * @note : Write data to file.
	 * @template Type : Type of the data to write.
	 * @param data : Reference to the variable used to store data to write.
	 * @return : Count of bytes writed to the file.
	 **/
	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	uint32_t Write( const Type& data ) {
		auto* buffer = micro_ptr_as( data, const uint8_t* );
		
		return Write( micro_sizeof( Type ), buffer );
	};

	/**
	 * Write template function
	 * @note : Write string to file.
	 * @param data : Query string to write.
	 * @return : Count of bytes writed to the file.
	 **/
	template<>
	uint32_t Write( const std::string& data ) {
		auto* buffer = micro_cast( data.c_str( ), const uint8_t* );
		auto length  = (uint32_t)data.size( );

		Write( length );

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
		requires ( !std::is_pointer<Type>::value )
	uint32_t Write( const std::vector<Type>& data ) {
		auto* buffer = micro_cast( data.data( ), const uint8_t* );
		auto length  = (uint32_t)data.size( );

		Write( length );

		return Write( length * micro_sizeof( Type ), buffer );
	};

public:
	/**
	 * GetIsValid const function
	 * @note : Get if the file is valid.
	 * @return : True for succes.
	 **/
	virtual bool GetIsValid( ) const;

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
	virtual uint32_t GetSize( ) const = 0;

	/**
	 * GetCursor const function
	 * @note : Get current file cursor position.
	 * @return : Return current file cursor position value.
	 **/
	virtual uint32_t GetCursor( ) const = 0;

	/**
	 * GetIsEOF const function
	 * @note : Get if the current handle has reached end of file.
	 * @return : Return true when file has reached end of file value.
	 **/
	virtual bool GetIsEOF( ) const = 0;

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

		return micro_self;
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

		return micro_self;
	};

};

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

#include "MicroFilePhysical.h"

micro_class MicroFileVirtual final : public MicroFile {

private:
	uint8_t* m_pointer;
	uint32_t m_length;

public:
	/**
	 * Constructor
	 **/
	MicroFileVirtual( );

	/**
	 * Copy-Constructor
	 * @param other : File to copy.
	 **/
	MicroFileVirtual( const MicroFileVirtual& other ) = delete;

	/**
	 * Move-Constructor
	 * @param other : File to move.
	 **/
	MicroFileVirtual( MicroFileVirtual&& other ) noexcept;

	/**
	 * Destructor
	 **/
	~MicroFileVirtual( ) = default;

	/**
	 * Open function
	 * @note : Open virtual file.
	 * @param mode : File opening mode, actualy same as native c fopen.
	 * @param type : Query file type.
	 * @return : True for succes.
	 **/
	bool Open(
		const void* data,
		const uint32_t length,
		const MicroFileAccessors accessor,
		const MicroFileTypes type
	);

	/**
	 * Seek procedure
	 * @note : Seek from current file position.
	 * @param offset : Offset in byte count.
	 **/
	virtual void Seek( const uint32_t offset ) override;

	/**
	 * SeekBegin procedure
	 * @note : Seek to begin of the file.
	 **/
	virtual void SeekBegin( ) override;

	/**
	 * SeekEnd procedure
	 * @note : Seek to end of the file.
	 **/
	virtual void SeekEnd( ) override;

	/**
	 * Read function
	 * @note : Read data from current file.
	 * @param length : Length of the buffer to store readed data.
	 * @param buffer : Pointer to the buffer to store readed data.
	 * @return : Count of bytes loaded to the buffer
	 **/
	virtual uint32_t Read( const uint32_t length, uint8_t* buffer ) override;

	/**
	 * Read function
	 * @note : Write data to current file.
	 * @param length : Length of the buffer to write.
	 * @param buffer : Pointer to the buffer to write.
	 * @return : Count of bytes writed to the file
	 **/
	virtual uint32_t Write(
		const uint32_t length,
		const uint8_t* buffer
	) override;

	/**
	 * Close procedure
	 * @note : Close current file.
	 **/
	virtual void Close( ) override;

public:
	/**
	 * GetIsValid const function
	 * @note : Get if the file is valid.
	 * @return : True for succes.
	 **/
	virtual bool GetIsValid( ) const override;

	/**
	 * GetSize const function
	 * @note : Get current file size.
	 **/
	virtual uint32_t GetSize( ) const override;

	/**
	 * GetNative const function
	 * @note : Get internal memory pointer.
	 * @return : Return memory pointer value.
	 **/
	void* GetNative( ) const;

public:
	/**
	 * GetNativeAs template const function
	 * @note : Get internal memory pointer casted as Type*.
	 * @template Type : Query internal memory type.
	 * @return : Return memory pointer value casted as Type*.
	 **/
	template<typename Type>
	Type* GetNativeAs( ) const {
		return micro_cast( GetNative( ), Type* );
	};

};

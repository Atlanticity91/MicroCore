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

#pragma once 

#include "MicroYamlReader.h"

micro_class MicroYamlWriter final { 

private:
	std::string m_path;
	YAML::Emitter m_emitter;

public:
	/**
	 * Constructor
	 **/
	MicroYamlWriter( );

	/**
	 * Destructor
	 **/
	~MicroYamlWriter( );

	/**
	 * Open function
	 * @note : Open file specified by the path.
	 * @param path : Path with extension to the query file.
	 * @return : True for succes.
	 **/
	bool Open( const std::string& path );

	/**
	 * Close procedure
	 * @note : Close current file.
	 **/
	void Close( );

public:
	/**
	 * << operator 
	 * @note : Write data to the file.
	 * @template Type : Type of data to write.
	 * @param data : Reference to the data to write.
	 **/
	template<typename Type>
	MicroYamlWriter& operator<<( const Type& data ) { 
		m_emitter << data;

		return micro_self;
	};

};

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

#include "MicroYaml.h"

micro_class MicroYamlReader final {

private:
	MicroFilePhysical m_file;
	YAML::Node m_document;

public:
	/**
	 * Constructor
	 **/
	MicroYamlReader( );

	/**
	 * Destructor
	 **/
	~MicroYamlReader( ) = default;

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
	 * Get function
	 * @note : Get current Yaml node handle.
	 **/
	YAML::Node& Get( );

public:
	/**
	 * Get template function
	 * @note : Get an element of the Yaml file by is name.
	 * @template Type : Type of the element.
	 * @param name : Name of the element to get.
	 **/
	template<typename Type>
	Type Get( const std::string& name ) {
		return m_document[ name ].as<Type>( );
	};

	/**
	 * Get template function
	 * @note : Get an element of the Yaml file by is name.
	 * @template Type : Type of the element.
	 * @param name : Name of the element to get.
	 **/
	template<typename Type>
	Type Get( micro_string name ) {
		return m_document[ name ].as<Type>( );
	};

public:
	/**
	 * [] operator
	 * @note : Get Yaml node by it's name.
	 * @param name : Name of the element.
	 **/
	YAML::Node operator[]( const std::string& name );

	/**
	 * [] operator
	 * @note : Get Yaml node by it's name.
	 * @param name : Name of the element.
	 **/
	YAML::Node operator[]( micro_string name );

public:
	/**
	 * () template operator
	 * @note : Get an element of the Yaml file, replace [] operator for template use.
	 * @template Type : Type of the element.
	 * @param name : Name of the element.
	 **/
	template<typename Type>
	Type operator()( const std::string name ) {
		return Get<Type>( name );
	};

	/**
	 * () template operator
	 * @note : Get an element of the Yaml file, replace [] operator for template use.
	 * @template Type : Type of the element.
	 * @param name : Name of the element.
	 **/
	template<typename Type>
	Type operator()( micro_string name ) {
		return Get<Type>( name );
	};

};

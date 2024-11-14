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

#include "MicroReflectEmitter.h"

class MicroReflectGenerator final : public MicroReflectEmitter {

public:
	/**
	 * Constructor
	 **/
	MicroReflectGenerator( );
	
	/**
	 * Destructor
	 **/
	virtual ~MicroReflectGenerator( ) = default;

	/**
	 * Run method
	 * @note : Generator run execution.
	 * @param declaration : Reference to query declaration.
	 **/
	virtual void Run( const MicroReflectSourceDeclaration& declaration ) override;

private:
	/**
	 * GenerateFields method
	 * @note : Generate fields output for the declaration.
	 * @param file : current output file.
	 * @param owner : Owner of the field.
	 * @param declaration : List of all fields to output.
	 **/
	void GenerateFields(
		std::ofstream& file,
		const std::string& owner,
		const std::vector<MicroReflectFieldDeclaration>& declaration
	);

	/**
	 * GenerateFunctions method
	 * @note : Generate functions output for the declaration.
	 * @param file : current output file.
	 * @param declaration : List of all functions to output.
	 **/
	void GenerateFunctions( 
		std::ofstream& file,
		const std::vector<MicroReflectFunctionDeclaration>& declaration
	);

	/**
	 * GenerateStruct method
	 * @note : Generate struct output for the declaration.
	 * @param file : current output file.
	 * @param declaration : struct to output.
	 **/
	void GenerateStruct( 
		std::ofstream& file,
		const MicroReflectStructDeclaration& declaration 
	);

	/**
	 * GenerateClass method
	 * @note : Generate class output for the declaration.
	 * @param file : current output file.
	 * @param declaration : class to output.
	 **/
	void GenerateClass( 
		std::ofstream& file,
		const MicroReflectClassDeclaration& declaration
	);

};

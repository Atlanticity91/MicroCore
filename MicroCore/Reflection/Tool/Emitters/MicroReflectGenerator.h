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

/**
 * MicroReflectGenerator class final
 * @note : Defined reflection system default emitter.
 **/
micro_class MicroReflectGenerator final : public MicroReflectEmitter {

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
	 * PreRun method
	 * @note : Executed after declaration generation, used to manually add
	 *		   declaration to the source.
	 * @param declaration : Current source declaration.
	 **/
	virtual void PreRun( MicroReflectSourceDeclaration& declaration ) override;

	/**
	 * Run method
	 * @note : Generator run execution.
	 * @param declaration : Reference to query declaration.
	 **/
	virtual void Run( const MicroReflectSourceDeclaration& declaration ) override;

private:
	/**
	 * GenerateEnum method
	 * @note : Generate enum output for the declaration.
	 * @param file : current output file.
	 * @param declaration : enum to output.
	 **/
	void GenerateEnum(
		std::ofstream& file,
		const MicroReflectEnumDeclaration& declaration
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
	 * GenerateAccessor function
	 * @note : Cast clang accessor to MicroReflectAccessor.
	 * @param accessor : Query clang accessor.
	 * @return : Return accessor as MicroReflectAccessor.
	 **/
	std::string GenerateAccessor( const MicroReflectAccessor accessor ) const;

	/**
	 * GenerateParents method
	 * @note : Generate functions output for the declaration.
	 * @param file : current output file.
	 * @param parents : List of all parents to output
	 **/
	void GenerateParents(
		std::ofstream& file,
		const std::vector<MicroReflectParentDeclaration>& parents
	);

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
	 * GenerateClass method
	 * @note : Generate class output for the declaration.
	 * @param file : current output file.
	 * @param declaration : class to output.
	 **/
	void GenerateClass( 
		std::ofstream& file,
		const MicroReflectClassDeclaration& declaration
	);

	/**
	 * GenerateNamespace method
	 * @note : Generate namespace output for the declaration.
	 * @param file : current output file.
	 * @param declaration : namespace to output.
	 **/
	void GenerateNamespace(
		std::ofstream& file,
		const MicroReflectNamespaceDeclaration& declaration
	);

private:
	bool GetCanReflect( const std::vector<std::string>& annotations ) const;

};

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

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroReflectGenerator::MicroReflectGenerator( ) 
	: MicroReflectEmitter{ }
{ }

void MicroReflectGenerator::PreRun( MicroReflectSourceDeclaration& declaration ) { }

void MicroReflectGenerator::Run( const MicroReflectSourceDeclaration& declaration ) {
	auto dst_path = declaration.Source;

	dst_path.replace_extension( ".reflect.h" );

	auto file = std::ofstream{ dst_path };

	file << "/**\n";
	file << " *\n";
	file << " *  __  __ _            ___      __ _        _\n";
	file << " * |  \\/  (_)__ _ _ ___| _ \\___ / _| |___ __| |_\n";
	file << " * | |\\/| | / _| '_/ _ \\   / -_)  _| / -_) _|  _|\n";
	file << " * |_|  |_|_\\__|_| \\___/_|_\\___|_| |_\\___\\__|\\__|\n";
	file << " *\n";
	file << " * Do not edit or delete.\n";
	file << " * This file was automatically generated by MicroReflectGenerator.\n";
	file << " * Contain reflection function implementation for types found in\n";
	file << " * source file : " << declaration.Source << "\n";
	file << " *\n";
	file << " **/\n\n";
	file << "#pragma once\n\n";
	file << "namespace micro {\n\n";

	GenerateNamespace( file, declaration );

	for ( const auto& namespace_declaration : declaration.Namespaces )
		GenerateNamespace( file, namespace_declaration );

	file << "\n};\n";

	file.close( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroReflectGenerator::GenerateEnum(
	std::ofstream& file,
	const MicroReflectEnumDeclaration& declaration
) {

	file << "\n";
}

void MicroReflectGenerator::GenerateFunctions(
	std::ofstream& file,
	const std::vector<MicroReflectFunctionDeclaration>& declaration
) {
	auto function_id = 0;

	for ( auto& function : declaration ) {
		if ( !GetCanReflect( function.Annotations ) )
			continue;

		file << "\t\t\t\tself->Functions[ " << std::to_string( function_id++ ) << " ] = { \""
			 << function.Name << "\",\n"
			 << "GetReflectType<" << function.ReturnType << ">( ),\n"
			 << "{}\n"
			 << GenerateAccessor( function.Accessor )
			 << " };\n";
	}

	file << "\n";
}

std::string MicroReflectGenerator::GenerateAccessor(
	const MicroReflectAccessor accessor
) const {
	auto result = std::string{ "MicroReflectVisibility::Public" };

	if ( accessor == MicroReflectAccessor::Protected )
		result = "MicroReflectVisibility::Protected";
	else if ( accessor == MicroReflectAccessor::Private )
		result = "MicroReflectVisibility::Private";

	return result;
}

void MicroReflectGenerator::GenerateParents(
	std::ofstream& file,
	const std::vector<MicroReflectParentDeclaration>& parents
) {
	auto parent_id = parents.size( );

	while ( parent_id-- > 0 ) {
		file << "\t\t\t\tself->Parents[ " << std::to_string( parent_id++ ) << " ] = { \""
			 << "GetReflectClass<" << parents[parent_id].Name << ">( ), "
			 << GenerateAccessor( parents[ parent_id ].Accessor )
			 << "\" };\n";
	}

	file << "\n";
}

void MicroReflectGenerator::GenerateFields(
	std::ofstream& file,
	const std::string& owner,
	const std::vector<MicroReflectFieldDeclaration>& declaration
) {
	auto field_id = 0;

	for ( auto& field : declaration ) {
		if ( !GetCanReflect( field.Annotations ) )
			continue;

		file << "\t\t\t\tself->Fields[ " << std::to_string( field_id++ ) << " ] = { \"" 
			 << field.Name << "\", offsetof( " << owner << ", " << field.Name << " ), GetType<" 
			 << field.Type << ">( ), "
			 << GenerateAccessor( field.Accessor ) << " };\n";
	}

	file << "\n";
}

void MicroReflectGenerator::GenerateClass(
	std::ofstream& file,
	const MicroReflectClassDeclaration& declaration
) {
	if ( !GetCanReflect( declaration.Annotations ) )
		return;

	auto& name = declaration.Name;

	file << "// === " << name << " ===\n";
	file << "\ttemplate<>\n\tfriend const ReflectClass* GetClassImpl( ReflectClassTag<" << name << "> ) noexcept {\n"
			<< "\t\tstatic auto storage_" << name << " = ReflectStorageClass<" 
				<< name << ", "
				<< declaration.Parents.size( ) << ", "
				<< declaration.Fields.size( ) << ", "
				<< declaration.Functions.size( ) 
				<< ">{\n"
			<< "\t\t\t\"" << name << "\"\n"
			<< "\t\t\t[]( auto* self ) {\n";

	GenerateParents( file, declaration.Parents );
	GenerateFields( file, name, declaration.Fields );
	GenerateFunctions( file, declaration.Functions );

	file << "\t\t\t}\n\t\t};\n"
		 << "\t\treturn storage_" << name << ";\n"
		 << "\t};\n\n";
}

void MicroReflectGenerator::GenerateNamespace(
	std::ofstream& file,
	const MicroReflectNamespaceDeclaration& declaration
) {
	for ( const auto& enum_declaration : declaration.Enumerations )
		GenerateEnum( file, enum_declaration );

	for ( const auto& function_declaration : declaration.Functions )
		GenerateFunctions( file, { function_declaration } );
	
	for ( const auto& class_declaration : declaration.Classes )
		GenerateClass( file, class_declaration );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
micro_inline bool MicroReflectGenerator::GetCanReflect(
	const std::vector<std::string>& annotations
) const {
	return FindAnnotation( annotations, "micro_reflect" );
}
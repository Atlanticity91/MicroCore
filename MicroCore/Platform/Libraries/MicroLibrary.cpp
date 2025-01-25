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
MicroLibrary::MicroLibrary( )
	: m_handle{ NULL },
	m_is_local{ false }, 
	m_path{ "" }, 
	m_root_procedure{ }
{ }

MicroLibrary::MicroLibrary( const std::string& path )
	: MicroLibrary{ std::move( path ), false }
{ }

MicroLibrary::MicroLibrary( const std::string& path, bool load_local )
	: MicroLibrary{ }
{
	Open( std::move( path ), load_local );
}

MicroLibrary::MicroLibrary( MicroLibrary&& other ) 
	: MicroLibrary{ }
{ 
	Close( );

	m_handle		 = other.m_handle;
	m_is_local		 = other.m_is_local;
	m_path			 = std::move( other.m_path );
	m_root_procedure = std::move( other.m_root_procedure );

	other.m_handle = NULL;
}

MicroLibrary::~MicroLibrary( ) {
	Close( );
}

bool MicroLibrary::Open( const std::string& path, bool load_local ) {
	auto* library_path = path.c_str( );

#	ifdef _WIN64
	if ( load_local )
		m_handle = GetModuleHandleA( library_path );
	else
		m_handle = LoadLibraryA( library_path );
#	else
	const auto flags = RTLD_NOW;

	if ( !load_local )
		flags |= RTLD_NOLOAD;

	m_handle = dlopen( library_path, flags );
#	endif

	if ( GetIsValid( ) )
		m_path = path;

	return GetIsValid( );
}

void* MicroLibrary::Acquire( const std::string& procedure) {
	auto* procedure_address = (void*)NULL;

	if ( GetIsValid( ) ) {
		auto* procedure_name = procedure.c_str( );

	#	ifdef _WIN64
		procedure_address = micro_cast( GetProcAddress( m_handle, procedure_name ), void* );
	#	else
		procedure_address = dlsym( m_handle, procedure_name );
	#	endif
	}

	return procedure_address;
}

bool MicroLibrary::Acquire( MicroLibraryProcedure& procedure ) {
	const auto& procedure_name = procedure.GetName( );

	if ( procedure = Acquire( procedure_name ) ) {
		auto* new_procedure = micro_ptr( procedure );

		m_root_procedure.Insert( new_procedure );
	}

	return procedure.GetIsCallable( );
}

void MicroLibrary::Release( MicroLibraryProcedure& procedure ) {
	procedure.~MicroLibraryProcedure( );
}

bool MicroLibrary::Close( ) {
	auto result = false;

	if ( GetIsValid( ) ) {
		FreeProcedures( );

	#	ifdef _WIN64
		result = ( FreeLibrary( m_handle ) == TRUE );
	#	else
		result = ( dlclose( m_handle ) == 0 );
	#	endif

		m_handle = NULL;
		m_path   = "";
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLibrary::FreeProcedures( ) {
	m_root_procedure.Free( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLibrary::GetIsValid( ) const {
	return m_handle != NULL;
}

bool MicroLibrary::GetIsLocal( ) const {
	return m_is_local;
}

const std::string& MicroLibrary::GetPath( ) const {
	return m_path;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLibrary::operator bool( ) const {
	return GetIsValid( );
}

void* MicroLibrary::operator[]( const std::string& procedure ) {
	return Acquire( std::move( procedure ) );
}

bool MicroLibrary::operator[]( MicroLibraryProcedure& procedure ) {
	return Acquire( procedure );
}

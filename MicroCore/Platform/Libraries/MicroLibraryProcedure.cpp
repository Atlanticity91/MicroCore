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
MicroLibraryProcedure::MicroLibraryProcedure( )
	: MicroLibraryProcedure{ "" }
{ }

MicroLibraryProcedure::MicroLibraryProcedure( const std::string& name )
	: m_name{ std::move( name ) },
	m_callable{ NULL },
	m_previous{ nullptr },
	m_next{ nullptr }
{ }

MicroLibraryProcedure::~MicroLibraryProcedure( ) {
	if ( m_previous != nullptr )
		m_previous->m_next = m_next;

	if ( m_next != nullptr )
		m_next->m_previous = m_previous;

	Reset( );
}


void MicroLibraryProcedure::Reset( ) {
	m_name	   = "";
	m_callable = NULL;
	m_previous = nullptr;
	m_next	   = nullptr;
}

void MicroLibraryProcedure::Insert( MicroLibraryProcedure* procedure ) {
	if ( procedure == nullptr )
		return;
}

void MicroLibraryProcedure::Free( ) { 
	auto* procedure = this;

	while ( procedure != nullptr ) {
		auto* swap = procedure->m_next;

		procedure->Reset( );

		procedure = swap;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLibraryProcedure::GetIsCallable( ) const {
	return !m_name.empty( ) && m_callable != NULL;
}

const std::string& MicroLibraryProcedure::GetName( ) const {
	return m_name;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLibraryProcedure::operator bool ( ) const {
	return GetIsCallable( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLibraryProcedure& MicroLibraryProcedure::operator=( void* callable ) {
	m_callable = callable;

	return micro_self;
}

MicroLibraryProcedure& MicroLibraryProcedure::operator=( MicroLibraryProcedure&& other ) {
	m_name	   = std::move( other.m_name );
	m_callable = other.m_callable;
	m_previous = other.m_previous;
	m_next	   = other.m_next;

	if ( m_previous != nullptr )
		m_previous->m_next = this;
	
	if ( m_next != nullptr  )
		m_next->m_previous = this;

	other.Reset( );

	return micro_self;
}

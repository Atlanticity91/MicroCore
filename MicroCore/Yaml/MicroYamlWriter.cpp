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

#include <__micro_core_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroYamlWriter::MicroYamlWriter( )
	: m_path{ },
	m_emitter{ }
{ }

MicroYamlWriter::~MicroYamlWriter( ) { 
	Close( );
}

bool MicroYamlWriter::Open( const std::string& path ) {
	auto* path_ = path.c_str( );

	return Open( path_ );
}

bool MicroYamlWriter::Open( micro_string path ) {
	m_path = path;
	m_emitter << YAML::BeginMap;

	return !m_path.empty( );
}

void MicroYamlWriter::Close( ) {
	if ( !m_path.empty( ) ) {
		auto file = MicroFile{ };

		if ( file.Open( m_path, MicroFileAccessors::Write, MicroFileTypes::Text ) ) {
			m_emitter << YAML::EndMap;

			auto* string = m_emitter.c_str( );
			auto length  = (uint32_t)strlen( string );

			file.Write( length, string );
			file.Close( );
		}

		m_path = "";
	}
}

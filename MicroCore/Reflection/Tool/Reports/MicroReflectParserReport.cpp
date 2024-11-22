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
MicroReflectParserReport::MicroReflectParserReport( 
	const MicroReflectParserReportModes mode 
)
	: m_mode{ mode },
	m_infos{ },
	m_warns{ },
	m_errrs{ }
{ }

void MicroReflectParserReport::SetReportMode( MicroReflectParserReportModes mode ) {
	m_mode = mode;
}

void MicroReflectParserReport::PushInfo( std::string&& report_line ) {
	m_infos.emplace_back( std::move( report_line ) );
}

void MicroReflectParserReport::PushWarn( std::string&& report_line ) {
	m_warns.emplace_back( std::move( report_line ) );
}

void MicroReflectParserReport::PushErrr( std::string&& report_line ) {
	m_errrs.emplace_back( std::move( report_line ) );
}

bool MicroReflectParserReport::Dump( const std::string& file ) {
	auto result = GetHasAny( );

	if ( result ) {
		auto report_text = GetReportText( file );

		for ( const auto& line : report_text )
			printf( "%s\n", line.c_str( ) );
	}

	return result;
}

bool MicroReflectParserReport::DumpLog( const std::string& file ) {
	auto result = GetHasAny( );

	if ( result ) {
		auto report_text = GetReportText( file );

		if ( !micro::get_logger( ) )
			micro::create_log( file, "./" );

		for ( const auto& line : report_text )
			micro::log_info( "{}", line );
	}

	return result;
}

bool MicroReflectParserReport::DumpFile(
	const std::string& path, 
	const std::string& file
) {
	auto path_ = std::filesystem::path{ path };

	return DumpFile( path_, std::move( file ) );
}

bool MicroReflectParserReport::DumpFile(
	const std::filesystem::path& path,
	const std::string& file
) {
	auto result = GetHasAny( );

	if ( result ) {
		auto report_text = GetReportText( file );
		auto dump_file = std::ofstream{ path };

		for ( auto&& line : report_text )
			dump_file << line;

		dump_file.close( );
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroReflectParserReport::GetReportTextList(
	std::vector<std::string>& report_text,
	const std::vector<std::string>& lines,
	const std::string& name
) {
	if ( lines.size( ) == 0 )
		return;

	report_text.emplace_back( std::move( name ) );

	for ( const auto& line : lines )
		report_text.emplace_back( line + "\n" );

	report_text.emplace_back( "\n" );
}

std::vector<std::string> MicroReflectParserReport::GetReportText( 
	const std::string& file 
) {
	auto report_text = std::vector<std::string>{ };

	auto info_count = m_infos.size( );
	auto warn_count = m_warns.size( );
	auto errr_count = m_errrs.size( );

	auto header = std::format(
		"=== MicroReflectParser : Report ===\nFile : {}\nInformations Count : {}\nWarnings Count : {}\nErrors Count : {}\n\n",
		file,
		info_count,
		warn_count,
		errr_count
	);

	report_text.emplace_back( std::move( header ) );

	GetReportTextList( report_text, m_infos, "Informations :\n" );
	GetReportTextList( report_text, m_warns, "Warnings :\n" );
	GetReportTextList( report_text, m_errrs, "Errors :\n" );

	return std::move( report_text );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroReflectParserReportModes MicroReflectParserReport::GetMode( ) const {
	return m_mode;
}

bool MicroReflectParserReport::GetHasFatal( ) const {
	return m_errrs.size( ) > 0;
}

bool MicroReflectParserReport::GetHasAny( ) const {
	auto result = false;

	switch ( m_mode ) {
		case MicroReflectParserReportModes::Warn : result = m_warns.size( ) > 0 || m_errrs.size( ) > 0; break;
		case MicroReflectParserReportModes::Errr : result = m_errrs.size( ) > 0; break;

		default : result = m_infos.size( ) > 0 || m_warns.size( ) > 0 || m_errrs.size( ) > 0; break;
	}

	return result;
}

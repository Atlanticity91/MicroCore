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

#include "MicroReflectParserReportModes.h"

/**
 * MicroReflectParserReport class final
 * @note : Defined reflection system parser error report representation.
 **/
micro_class MicroReflectParserReport final { 

private:
	MicroReflectParserReportModes m_mode;
	std::vector<std::string> m_infos;
	std::vector<std::string> m_warns;
	std::vector<std::string> m_errrs;

public:
	/**
	 * Constructor
	 * @param mode : Query report mode.
	 **/
	MicroReflectParserReport( const MicroReflectParserReportModes mode );

	/**
	 * Destructor
	 **/
	~MicroReflectParserReport( ) = default;

	/**
	 * SetReportMode method
	 * @note : Set report mode.
	 * @param mode : Query report mode.
	 **/
	void SetReportMode( MicroReflectParserReportModes mode );

	/**
	 * PushInfo method
	 * @note : Push a report line to informations list.
	 * @param report_line : Query report line.
	 **/
	void PushInfo( std::string&& report_line );

	/**
	 * PushWarn method
	 * @note : Push a report line to warnings list.
	 * @param report_line : Query report line.
	 **/
	void PushWarn( std::string&& report_line );
	
	/**
	 * PushErrr method
	 * @note : Push a report line to errors list.
	 * @param report_line : Query report line.
	 **/
	void PushErrr( std::string&& report_line );

	/**
	 * Dump method
	 * @note : Dump parser report to console.
	 * @param file : Query parser report source file.
	 * @return : Return true when report as been dumped.
	 **/
	bool Dump( const std::string& file );

	/**
	 * DumpLog method
	 * @note : Dump parser report to logs.
	 * @param file : Query parser report source file.
	 * @return : Return true when report as been dumped.
	 **/
	bool DumpLog( const std::string& file );

	/**
	 * DumpFile method
	 * @note : Dump parser report to file.
	 * @param path : Path to the file directory.
	 * @param file : Query parser report source file.
	 * @return : Return true when report as been dumped.
	 **/
	bool DumpFile(
		const std::string& path,
		const std::string& file
	);

	/**
	 * DumpFile method
	 * @note : Dump parser report to file.
	 * @param path : Path to the file directory.
	 * @param file : Query parser report source file.
	 * @return : Return true when report as been dumped.
	 **/
	bool DumpFile( 
		const std::filesystem::path& path,
		const std::string& file
	);

private:
	/**
	 * GetReportTextList method
	 * @note : Get report text line to report text list.
	 * @param report_text : Query report text list.
	 * @param lines : Query repot lines to export.
	 * @param name : Name of the report line category.
	 **/
	void GetReportTextList(
		std::vector<std::string>& report_text,
		const std::vector<std::string>& lines,
		const std::string& name
	);

	/**
	 * GetReportText function
	 * @note : Get formated report value.
	 * @param file : Query report source file.
	 * @return : Return current report as text list.
	 **/
	std::vector<std::string> GetReportText( const std::string& file );

public:
	/**
	 * GetMode const function
	 * @note : Get current report mode.
	 * @return : Return current report mode value.
	 **/
	MicroReflectParserReportModes GetMode( ) const;
	
	/**
	 * GetHasFatal const function
	 * @note : Get if report contain any fatal error.
	 * @return : Return true when report contain at leat one fatal error.
	 **/
	bool GetHasFatal( ) const;

	/**
	 * GetHasAny const function
	 * @note : Get if report contain data.
	 * @return : Return true when report contain any informations.
	 **/
	bool GetHasAny( ) const;

};

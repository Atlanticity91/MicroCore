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

#include "../Maths/MicroMath.h"

#pragma warning( push, 0 )
#	include <spdlog/spdlog.h>
#	include <spdlog/fmt/ostr.h>
#	include <spdlog/sinks/daily_file_sink.h>
#	include <spdlog/sinks/dist_sink.h>
#	include <spdlog/sinks/basic_file_sink.h>
#	include <spdlog/sinks/stdout_color_sinks.h>
#pragma warning( pop )

namespace micro { 

	/**
	 * create_log function
	 * @note : Create the internal logger with console + file output.
	 * @param name : Name of the logger.
	 * @param path : Path to the log file.
	 **/
	MICRO_API bool create_log( const std::string& name, const std::string& path );

	/**
	 * create_log function
	 * @note : Create the internal logger with console + file output.
	 * @param name : Name of the logger.
	 * @param path : Path to the log file.
	 **/
	MICRO_API bool create_log( micro_string name, micro_string path );

	/**
	 * get_logger function
	 * @note : Get the internal logger value.
	 **/
	MICRO_API std::shared_ptr<spdlog::logger> get_logger( );

	/**
	 * log_trace templace procedure
	 * @note : Emit a log with trace as message level.
	 * @param fmt : Format of the log.
	 * @param args : Arguments to pass as format parameters.
	 **/
	template<typename... Args>
	void log_trace( spdlog::format_string_t<Args...> fmt, Args&&...args ) {
		auto logger = get_logger( );

		if ( logger != nullptr )
			logger->trace( fmt, std::forward<Args>( args )... );
	};

	/**
	 * log_info templace procedure
	 * @note : Emit a log with information as message level.
	 * @param fmt : Format of the log.
	 * @param args : Arguments to pass as format parameters.
	 **/
	template<typename... Args>
	void log_info( spdlog::format_string_t<Args...> fmt, Args&&...args ) {
		auto logger = get_logger( );

		if ( logger != nullptr )
			logger->info( fmt, std::forward<Args>( args )... );
	};

	/**
	 * log_warn templace procedure
	 * @note : Emit a log with warning as message level.
	 * @param fmt : Format of the log.
	 * @param args : Arguments to pass as format parameters.
	 **/
	template<typename... Args>
	void log_warn( spdlog::format_string_t<Args...> fmt, Args&&...args ) {
		auto logger = get_logger( );

		if ( logger != nullptr )
			logger->warn( fmt, std::forward<Args>( args )... );
	};

	/**
	 * log_errr templace procedure
	 * @note : Emit a log with error as message level.
	 * @param fmt : Format of the log.
	 * @param args : Arguments to pass as format parameters.
	 **/
	template<typename... Args>
	void log_errr( spdlog::format_string_t<Args...> fmt, Args&&...args ) {
		auto logger = get_logger( );

		if ( logger != nullptr )
			logger->error( fmt, std::forward<Args>( args )... );
	};

};

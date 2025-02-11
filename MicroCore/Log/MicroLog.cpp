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

#include "__micro_core_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<spdlog::logger> internal_logger{ nullptr };

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace micro {

	bool create_log( const std::string& name, const std::string& path ) {
		auto* name_ = name.c_str( );
		auto* path_ = path.c_str( );

		return create_log( name_, path_ );
	}

	bool create_log( micro_string name, micro_string path ) {
		auto sinks = std::vector<spdlog::sink_ptr>{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>( ),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>( path, true )
		};

		sinks[ 0 ]->set_pattern( "%^[ %T ] %n: %v%$" );
		sinks[ 1 ]->set_pattern( "[ %T ][ %l ] %n: %v" );

		internal_logger = std::make_shared<spdlog::logger>( name, begin( sinks ), end( sinks ) );

		internal_logger->set_level( spdlog::level::trace );
		internal_logger->flush_on( spdlog::level::trace );

		spdlog::register_logger( internal_logger );

		return internal_logger != nullptr;
	}

	std::shared_ptr<spdlog::logger> get_logger( ) {
		return internal_logger;
	}

};

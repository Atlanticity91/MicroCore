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
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace micro {

	BenchReport Bench(
		micro_string name,
		std::initializer_list<uint32_t> step_counts,
		std::function<double( BenchTimer& timer, uint32_t )> lambda
	) {
		auto step_id = step_counts.size( );
		auto report = BenchReport{ name, (uint32_t)step_id };
		auto timer = BenchTimer{ };

		while ( step_id-- > 0 ) {
			auto& result = report.Results[ step_id ];

			result.Steps	= micro_ref( step_counts.begin( ) + step_id );
			result.Duration = std::invoke( lambda, timer, result.Steps );
		}

		return std::move( report );
	}

	BenchReport Bench(
		std::string& report_string,
		micro_string name,
		std::initializer_list<uint32_t> step_counts,
		std::function<double( BenchTimer& timer, uint32_t )> lambda
	) {
		auto report = Bench( name, step_counts, lambda );

		report_string = std::format( "{} : {}\n", name, step_counts.size( ) );

		for ( const auto& result : report.Results )
			report_string += std::format( "\t{:6}/{}\n", result.Steps, result.Duration );

		return std::move( report );
	}

};

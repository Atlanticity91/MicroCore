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

#include "BenchReport.h"

namespace micro {

	/**
	 * Bench function
	 * @note : Run elementary benchmark.
	 * @param name : Query bench function name.
	 * @param step_counts : Number of steps foreach lambda execution.
	 * @param lambda : Query lambda to bench.
	 * @return : Return benchmark result.
	 **/
	MICRO_API BenchReport Bench(
		micro_string name,
		std::initializer_list<uint32_t> step_counts,
		std::function<double( BenchTimer& timer, uint32_t )> lambda
	);

	/**
	 * Bench function
	 * @note : Run elementary benchmark.
	 * @param report_string : Query formated string report.
	 * @param name : Query bench function name.
	 * @param step_counts : Number of steps foreach lambda execution.
	 * @param lambda : Query lambda to bench.
	 * @return : Return benchmark result.
	 **/
	MICRO_API BenchReport Bench(
		std::string& report_string,
		micro_string name,
		std::initializer_list<uint32_t> step_counts,
		std::function<double( BenchTimer& timer, uint32_t )> lambda
	);

};

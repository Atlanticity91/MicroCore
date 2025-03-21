/**
 *
 *  __  __ _           _____       _
 * |  \/  (_)__ _ _ __|_   _|__ __| |_
 * | |\/| | / _| '_/ _ \| |/ -_|_-<  _|
 * |_|  |_|_\__|_| \___/|_|\___/__/\__|
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

#include "CppUnitTest.h"
#include <MicroCore.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

////////////////////////////////////////////////////////////////////////////////////////////
//		===	TEST ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace UnitBench {

	TEST_CLASS( MicroBench ) {

	public:
		TEST_METHOD( BenchVector ) {
			auto report_string = std::string{ "" };
			auto report = micro::Bench(
				report_string,
				"Vector<uint32_t>",
				{ 100, 1000, 10000 },
				[]( micro::BenchTimer& timer, uint32_t steps ) {
					auto vec = std::vector<uint32_t>{ };
					auto s = steps;

					timer.Start( );

					while ( steps-- > 0 )
						vec.emplace_back( steps * s + steps - s );

					return timer.Resolve( );
				}
			);

			auto* message = report_string.c_str( );

			Logger::WriteMessage( message );
		};

	};

};

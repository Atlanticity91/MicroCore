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
namespace UnitTest {

	TEST_CLASS( MicroPlatform ) {

	public:
		TEST_METHOD( Copy ) {
			auto var_a = 1240;
			auto var_b = 0;

			micro::copy( var_a, var_b );

			Assert::AreEqual( var_a, var_b );
		};
		
		TEST_METHOD( Move ) {
			auto var_a = 1240;
			auto var_b = 0;

			micro::move( var_a, var_b );

			Assert::AreEqual( var_a, var_b );
		};

	};

};

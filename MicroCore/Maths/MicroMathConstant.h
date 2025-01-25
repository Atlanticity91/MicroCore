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

#pragma once

#include "MicroMat4.h"

// === PI : FLOAT ===
#define MICRO_MAX_FLOAT    ( 3.402823466e+38f )
#define MICRO_PI_F 		   ( 3.1415926535897932f )
#define MICRO_PI_INVERSE_F ( 0.31830988618f )
#define MICRO_PI_SQUARED_F ( 9.86960440108f )
#define MICRO_HALF_PI_F	   ( 1.57079632679f )
#define MICRO_TWO_PI_F	   ( 6.28318530717f )

// === PI : DOUBLE ===
#define MICRO_PI_D		   ( 3.141592653589793238462643383279502884197169399 )
#define MICRO_PI_INVERSE_D ( 0.31830988618379067154 )
#define MICRO_PI_SQUARED_D ( 9.86960440108935861883 )
#define MICRO_HALF_PI_D	   ( 1.57079632679489661923 )
#define MICRO_TWO_PI_D	   ( 6.28318530717958647692 )

// === GOLDEN RATIO ===
#define MICRO_GOLDEN_RATIO_F ( 1.6180339887498948482045868343656381f )
#define MICRO_GOLDEN_RATIO_D ( 1.6180339887498948482045868343656381 )

// === SQUARE ROOTS : FLOAT ===
#define MICRO_SQRT_2_F		   ( 1.4142135623730950488016887242097f )
#define MICRO_SQRT_3_F		   ( 1.7320508075688772935274463415059f )
#define MICRO_INVERSE_SQRT_2_F ( 0.70710678118654752440084436210485f )
#define MICRO_INVERSE_SQRT_3_F ( 0.57735026918962576450914878050196f )
#define MICRO_HALF_SQRT_2_F	   ( 0.70710678118654752440084436210485f )
#define MICRO_HALF_SQRT_3_F	   ( 0.86602540378443864676372317075294f )

// === SQUARE ROOTS : DOUBLE ===
#define MICRO_DOUBLE_SQRT_2_D		  ( 1.4142135623730950488016887242097 )
#define MICRO_DOUBLE_SQRT_3_D		  ( 1.7320508075688772935274463415059 )
#define MICRO_DOUBLE_INVERSE_SQRT_2_D ( 0.70710678118654752440084436210485 )
#define MICRO_DOUBLE_INVERSE_SQRT_3_D ( 0.57735026918962576450914878050196 )
#define MICRO_DOUBLE_HALF_SQRT_2_D	  ( 0.70710678118654752440084436210485 )
#define MICRO_DOUBLE_HALF_SQRT_3_D    ( 0.86602540378443864676372317075294 )

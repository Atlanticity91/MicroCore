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
#define micro_max_float    ( 3.402823466e+38f )
#define micro_pi_f 		   ( 3.1415926535897932f )
#define micro_pi_inverse_f ( 0.31830988618f )
#define micro_pi_squared_f ( 9.86960440108f )
#define micro_half_pi_f	   ( 1.57079632679f )
#define micro_two_pi_f	   ( 6.28318530717f )

// === PI : DOUBLE ===
#define micro_pi_D		   ( 3.141592653589793238462643383279502884197169399 )
#define micro_pi_inverse_D ( 0.31830988618379067154 )
#define micro_pi_squared_D ( 9.86960440108935861883 )
#define micro_half_pi_D	   ( 1.57079632679489661923 )
#define micro_two_pi_D	   ( 6.28318530717958647692 )

// === GOLDEN RATIO ===
#define micro_golden_ratio_f ( 1.6180339887498948482045868343656381f )
#define micro_golden_ratio_D ( 1.6180339887498948482045868343656381 )

// === SQUARE ROOTS : FLOAT ===
#define micro_sqrt_2_f		   ( 1.4142135623730950488016887242097f )
#define micro_sqrt_3_f		   ( 1.7320508075688772935274463415059f )
#define micro_inverse_sqrt_2_f ( 0.70710678118654752440084436210485f )
#define micro_inverse_sqrt_3_f ( 0.57735026918962576450914878050196f )
#define micro_half_sqrt_2_f	   ( 0.70710678118654752440084436210485f )
#define micro_half_sqrt_3_f	   ( 0.86602540378443864676372317075294f )

// === SQUARE ROOTS : DOUBLE ===
#define micro_double_sqrt_2_D		  ( 1.4142135623730950488016887242097 )
#define micro_double_sqrt_3_D		  ( 1.7320508075688772935274463415059 )
#define micro_double_inverse_sqrt_2_D ( 0.70710678118654752440084436210485 )
#define micro_double_inverse_sqrt_3_D ( 0.57735026918962576450914878050196 )
#define micro_double_half_sqrt_2_D	  ( 0.70710678118654752440084436210485 )
#define micro_double_half_sqrt_3_D    ( 0.86602540378443864676372317075294 )

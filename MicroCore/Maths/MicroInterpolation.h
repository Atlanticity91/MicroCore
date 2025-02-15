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

#include "MicroMathConstant.h"

namespace micro_math {

	template<typename Type>
	micro_nodiscard inline Type lerp(
		const Type& source, 
		const Type& destination,
		const float alpha
	) {
		return source + alpha * ( destination - source );
	};

	template<typename Type>
	micro_nodiscard inline Type lerp_stable(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		return source * ( 1.f - alpha ) + destination * alpha;
	};

	template<typename Type>
	micro_nodiscard Type interp_ease_in(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) {
		const auto scalar = std::pow( alpha, exponent );

		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_ease_out(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) {
		const auto scalar = 1.f - std::pow( 1.f - alpha, exponent );

		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_ease_in_out(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) { 
		const auto scalar = ( alpha < 0.5f ) ? 
							micro_math::interp_ease_in(  0.f, 1.f, alpha * 2.f	  , exponent ) * 0.5f :
							micro_math::interp_ease_out( 0.f, 1.f, alpha * 2.f - 1.f, exponent );

		return micro_math::lerp( source, destination, scalar * 0.5f + 0.5f );
	};

	template<typename Type>
	micro_nodiscard Type interp_sin_in(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = -1.f * std::cos( alpha * micro_half_pi_f ) + 1.f;

		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_sin_out(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = std::sin( alpha * micro_half_pi_f );
		
		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_sin_in_out(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha < 0.5f ) ?
							micro_math::interp_sin_in(  0.f, 1.f, alpha * 2.f		  ) * 0.5f :
							micro_math::interp_sin_out( 0.f, 1.f, alpha * 2.f - 1.f );

		return micro_math::lerp( source, destination, scalar * 0.5f + 0.5f );
	};

	template<typename Type>
	micro_nodiscard Type interp_expo_in(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha == 0.f ) ? 0.f : std::pow( 2.f, 10.f * ( alpha - 1.f ) );

		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_expo_out(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha == 1.f ) ? 1.f : -std::pow( 2.f, -10.f * alpha ) + 1.f;
		
		return micro_math::lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type interp_expo_in_out(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha < 0.5f ) ?
							micro_math::interp_expo_in(  0.f, 1.f, alpha * 2.f	   ) * 0.5f :
							micro_math::interp_expo_out( 0.f, 1.f, alpha * 2.f - 1.f );

		return micro_math::lerp( source, destination, scalar * 0.5f + 0.5f );
	};

};

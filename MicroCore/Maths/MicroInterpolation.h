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

#include "MicroMathConstant.h"

namespace micro {

	/**
	 * Lerp template function
	 * @note : Perform linear interpolation between source and destination.
	 * @template Type : Type of the element to lerp.
	 * @param source : Query source value.
	 * @param destination : Query destination value.
	 * @param alpha : Scalar controlling interpolation in range [ 0.f : 1.f ]
	 * @return : Return interpolation between source and destination by alpha.
	 **/
	template<typename Type>
	micro_nodiscard inline Type Lerp(
		const Type& source, 
		const Type& destination,
		const float alpha
	) {
		return source + alpha * ( destination - source );
	};

	/**
	 * LerpStable function
	 * @note : Perform linear interpolation between source and destination.
	 * @template Type : Type of the element to lerp.
	 * @param source : Query source value.
	 * @param destination : Query destination value.
	 * @param alpha : Scalar controlling interpolation in range [ 0.f : 1.f ]
	 * @return : Return interpolation between source and destination by alpha.
	 **/
	template<typename Type>
	micro_nodiscard inline Type LerpStable(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		return source * ( 1.f - alpha ) + destination * alpha;
	};

	template<typename Type>
	micro_nodiscard Type InterpEaseIn(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) {
		const auto scalar = std::pow( alpha, exponent );

		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpEaseOut(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) {
		const auto scalar = 1.f - std::pow( 1.f - alpha, exponent );

		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpEaseInOut(
		const Type& source,
		const Type& destination,
		const float alpha,
		const float exponent
	) { 
		const auto scalar = ( alpha < 0.5f ) ? 
							InterpEaseIn(  0.f, 1.f, alpha * 2.f	  , exponent ) * 0.5f :
							InterpEaseOut( 0.f, 1.f, alpha * 2.f - 1.f, exponent );

		return Lerp( source, destination, scalar * 0.5f + 0.5f );
	};

	template<typename Type>
	micro_nodiscard Type InterpSinIn(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = -1.f * std::cos( alpha * MICRO_HALF_PI_F ) + 1.f;

		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpSinOut(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = std::sin( alpha * MICRO_HALF_PI_F );
		
		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpSinInOut(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha < 0.5f ) ?
							InterpSinIn(  0.f, 1.f, alpha * 2.f		  ) * 0.5f :
							InterpSinOut( 0.f, 1.f, alpha * 2.f - 1.f );

		return Lerp( source, destination, scalar * 0.5f + 0.5f );
	};

	template<typename Type>
	micro_nodiscard Type InterpExpoIn(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha == 0.f ) ? 0.f : std::pow( 2.f, 10.f * ( alpha - 1.f ) );

		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpExpoOut(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha == 1.f ) ? 1.f : -std::pow( 2.f, -10.f * alpha ) + 1.f;
		
		return Lerp( source, destination, scalar );
	};

	template<typename Type>
	micro_nodiscard Type InterpExpoInOut(
		const Type& source,
		const Type& destination,
		const float alpha
	) {
		const auto scalar = ( alpha < 0.5f ) ?
							InterpExpoIn(  0.f, 1.f, alpha * 2.f	   ) * 0.5f :
							InterpExpoOut( 0.f, 1.f, alpha * 2.f - 1.f );

		return Lerp( source, destination, scalar * 0.5f + 0.5f );
	};

};

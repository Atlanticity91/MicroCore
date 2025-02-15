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

#include "MicroMath.h"

template<typename Literal, Literal(*HasingFunctor)( const uint32_t, micro_string )>
	requires ( HasingFunctor != nullptr )
class micro_hash final {

private:
	Literal m_hash;

public:
	micro_hash( )
		: m_hash{ 0 } 
	{ };

	micro_hash( micro_string value )
		: micro_hash{ } 
	{
		const auto length = (uint32_t)strlen( value );

		m_hash = std::invoke( HasingFunctor, length, value );
	};

	explicit micro_hash( const std::string& value )
		: micro_hash{ } 
	{
		const auto* data = value.c_str( );
		const auto length = (uint32_t)value.size( );

		m_hash = std::invoke( HasingFunctor, length, data );
	};

	micro_hash( const micro_hash& other )
		: m_hash{ other.m_hash }
	{ };

	micro_hash( micro_hash&& other ) noexcept
		: m_hash{ std::move( other.m_hash ) } 
	{ };

	~micro_hash( ) = default;

public:
	bool GetIsValid( ) const {
		return m_hash != 0;
	};

	Literal Get( ) const {
		return m_hash;
	};

public:
	operator bool( ) const {
		return GetIsValid( );
	};

	operator Literal ( ) const {
		return Get( );
	};

	micro_hash& operator=( micro_string value ) {
		const auto length = (uint32_t)strlen( value );

		m_hash = std::invoke( HasingFunctor, length, value );

		return micro_self;
	};

	micro_hash& operator=( const std::string& value ) {
		const auto* data  = value.c_str( );
		const auto length = (uint32_t)value.size( );

		m_hash = std::invoke( HasingFunctor, length, data );

		return micro_self;
	};

	micro_hash& operator=( const micro_hash& other ) {
		m_hash = other.m_hash;
		
		return micro_self;
	};

	micro_hash& operator=( micro_hash&& other ) noexcept { 
		m_hash = std::move( other.m_hash );

		return micro_self;
	};

	bool operator<( micro_string value ) const {
		const auto other = micro_hash{ value };

		return micro_self < other;
	};

	bool operator<( const std::string& value ) const {
		const auto other = micro_hash{ value };

		return micro_self < other;
	};

	bool operator<( const micro_hash& other ) const {
		return m_hash < other.m_hash;
	};
	
	bool operator>( micro_string value ) const {
		const auto other = micro_hash{ value };

		return micro_self > other;
	};

	bool operator>( const std::string& value ) const {
		const auto other = micro_hash{ value };

		return micro_self > other;
	};

	bool operator>( const micro_hash& other ) const {
		return m_hash > other.m_hash;
	};

	bool operator==( micro_string value ) const { 
		const auto other = micro_hash{ value };

		return micro_self == other;
	};
	
	bool operator==( const std::string& value ) const {
		const auto other = micro_hash{ value };

		return micro_self == other;
	};

	bool operator==( const micro_hash& other ) const { 
		return m_hash == other.m_hash;
	};

	bool operator!=( micro_string value ) const {
		return !( micro_self == value );
	};

	bool operator!=( const std::string& value ) const {
		return !( micro_self == value );
	};

	bool operator!=( const micro_hash& other ) const { 
		return !( micro_self == other );
	};

};

typedef micro_hash<uint32_t, micro_math::hash32> micro_hash32;
typedef micro_hash<uint64_t, micro_math::hash64> micro_hash64;

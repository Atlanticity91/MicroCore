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

#include "MicroOS.h"

template<typename Return, typename... Args>
class MicroCallable final {

	using Signature_t = std::function<Return( Args... )>;

private:
	Signature_t m_invocable;

public:
	MicroCallable( )
		: m_invocable{ } 
	{ };

	explicit MicroCallable( Signature_t invocable )
		: m_invocable{ std::move( invocable ) } 
	{ };

	MicroCallable( const MicroCallable& other )
		: m_invocable{ other.m_invocable } 
	{ };

	MicroCallable( MicroCallable&& other ) noexcept
		: m_invocable{ std::move( other.m_invocable ) } 
	{ };

	~MicroCallable( ) = default;

	Return Invoke( Args&&... args ) const {
		if ( m_invocable )
			return std::invoke( m_invocable, std::forward<Args>( args )... );

		if constexpr ( !std::is_void<Return>::value )
			return Return{ };
	};

public:
	explicit operator bool( ) const {
		return (bool)m_invocable;
	};

	Return operator( )( Args&&... args ) const {
		return Invoke( std::forward<Args>( args )... );
	};

	MicroCallable& operator=( Signature_t invocable ) noexcept {
		m_invocable = std::move( invocable );

		return *this;
	};

	MicroCallable& operator=( const MicroCallable& other ) noexcept {
		m_invocable = other.m_invocable;

		return *this;
	};

	MicroCallable& operator=( MicroCallable&& other ) noexcept {
		m_invocable = std::move( other.m_invocable );

		return *this;
	};

};

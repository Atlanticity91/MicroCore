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
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#define MDA_BUFFER_SIZE 16384
#define MDA_BUFFER_LENGTH ( MDA_BUFFER_SIZE * micro_sizeof( char ) )

static uint32_t mda_offset = 0;
static char mda_buffer[ MDA_BUFFER_SIZE ] = { '\0' };

#ifdef _MSC_VER 
//#	include <winsock2.h>
//#	pragma comment( lib, "ws2_32.lib" )

static SOCKET mda_socket   = INVALID_SOCKET;
#else
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroDebugAdapterError MicroDebugAdapter::Connect( 
    const MicroDebugAdapterSpecification& specification
) {
	auto result = MicroDebugAdapterError::None;

#   ifdef _MSC_VER
    auto wsa_data = WSADATA{ };

    if ( WSAStartup( MAKEWORD( 2, 2 ), micro_ptr( wsa_data ) ) == 0 ) {
        mda_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        if ( mda_socket != INVALID_SOCKET ) {
            auto socket_address = sockaddr_in{ };

            socket_address.sin_family = AF_INET;
            socket_address.sin_port = htons( specification.Port );
            socket_address.sin_addr.s_addr = inet_addr( specification.Address );

            if ( connect( mda_socket, micro_ptr_as( socket_address, sockaddr* ), sizeof( sockaddr_in ) ) < 0 ) {
                closesocket( mda_socket );
                WSACleanup( );

                result = MicroDebugAdapterError::NetError_ConnectionFail;
            }
        } else {
            WSACleanup( );

            result = MicroDebugAdapterError::NetError_CreationFail;
        }
    } else
        result = MicroDebugAdapterError::NetError_InitializeFail;
#   else
#   endif

	return result;
}

MicroDebugAdapterError MicroDebugAdapter::Broadcast( 
	const MicroDebugEvent* event_specification 
) {
	auto result = MicroDebugAdapterError::None;

	if ( event_specification != nullptr && event_specification->GetIsValid( ) ) {
#       ifdef _MSC_VER
        if ( mda_socket != INVALID_SOCKET ) {
            const auto message  = event_specification->ToString( );
            auto* message_value = message.c_str( );
            auto message_length = (uint32_t)message.length( );

            if ( send( mda_socket, message_value, message_length, 0 ) == SOCKET_ERROR )
                result = MicroDebugAdapterError::NetError_BroadcastFail;
        } else
            result = MicroDebugAdapterError::NetError_Invalid;
#       else
#       endif
	} else
		result = MicroDebugAdapterError::EventError_Invalid;

	return result;
}

MicroDebugAdapterError MicroDebugAdapter::Receive( MicrDebugEventTypes& event_type ) {
	auto result = MicroDebugAdapterError::None;

#   ifdef _MSC_VER
    if ( mda_socket != INVALID_SOCKET ) {
        auto receive_length = recv( mda_socket, mda_buffer, MDA_BUFFER_LENGTH, 0 );

        if ( receive_length == SOCKET_ERROR ) {
            mda_offset      = 0;
            mda_buffer[ 0 ] = '\0';

            result = MicroDebugAdapterError::NetError_ReceiveFail;
        } else
            mda_offset = (uint32_t)receive_length;
    } else
        result = MicroDebugAdapterError::NetError_Invalid;
#   else
#   endif

	return result;
}

MicroDebugAdapterError MicroDebugAdapter::Disconnect( ) {
	auto result = MicroDebugAdapterError::None;

#   ifdef _MSC_VER
    if ( mda_socket != INVALID_SOCKET ) {
        if ( shutdown( mda_socket, 2 ) != SOCKET_ERROR ) {
            if ( closesocket( mda_socket ) == SOCKET_ERROR )
                result = MicroDebugAdapterError::NetError_DisconnectFail;
        } else
            result = MicroDebugAdapterError::NetError_ShutdownFail;

        WSACleanup( );
    } else
        result = MicroDebugAdapterError::NetError_Invalid;
#   endif

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
uint32_t MicroDebugAdapter::GetBufferSize( ) {
    return MDA_BUFFER_SIZE;
}

const char* MicroDebugAdapter::GetBufferData( ) {
    return mda_buffer;
}

const MicroDebugAdapterBuffer MicroDebugAdapter::GetBuffer( ) {
    return { MDA_BUFFER_SIZE, mda_offset, mda_buffer };
}

constexpr std::string MicroDebugAdapter::ToString( const MicroDebugMessageTypes type ) {
    switch ( type ) {
        case MicroDebugMessageTypes::Request  : return "request";
        case MicroDebugMessageTypes::Response : return "response";
        case MicroDebugMessageTypes::Event    : return "event";

        default : break;
    }

    return "";
}

constexpr std::string MicroDebugAdapter::ToString( const bool value ) {
    return value ? "true" : "false";
}

constexpr std::string MicroDebugAdapter::ToString(
    const MicroDebugEventReasons reason
) {
    switch ( reason ) {
        // STOPPED
        case MicroDebugEventReasons::Step                  : return "step";
        case MicroDebugEventReasons::Breakpoint            : return "breakpoint";
        case MicroDebugEventReasons::Exception             : return "exception";
        case MicroDebugEventReasons::Pause                 : return "pause";
        case MicroDebugEventReasons::Entry                 : return "entry";
        case MicroDebugEventReasons::Goto                  : return "goto";
        case MicroDebugEventReasons::FunctionBreakpoint    : return "function breakpoint";
        case MicroDebugEventReasons::DataBreakpoint        : return "data breakpoint";
        case MicroDebugEventReasons::InstructionBreakpoint : return "instruction breakpoint";

        // BREAKPOINT
        case MicroDebugEventReasons::Changed               : return "changed";
        case MicroDebugEventReasons::New                   : return "new";
        case MicroDebugEventReasons::Removed               : return "removed";

        // THREAD
        case MicroDebugEventReasons::Started               : return "started";
        case MicroDebugEventReasons::Exited                : return "exited";

        default: break;
    }

    return "none";
}

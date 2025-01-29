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
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroDebugEventContinued::MicroDebugEventContinued( ) 
	: MicroDebugEventContinued{ 0, false }
{ }

MicroDebugEventContinued::MicroDebugEventContinued(
	const uint32_t sequence, 
	const uint32_t thread_id 
)
	: MicroDebugEventContinued{ sequence, thread_id, false }
{ }

MicroDebugEventContinued::MicroDebugEventContinued(
	const uint32_t sequence,
	const uint32_t thread_id,
	const bool all_thread_stopped
)
	: MicroDebugEvent{ sequence, MicrDebugEventTypes::Continued },
	ThreadID{ thread_id },
	AllThreadsStopped{ all_thread_stopped }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
std::string MicroDebugEventContinued::ToString( ) const {
	const auto header = MicroDebugMessage::GetHeader( );
	const auto all_threads_stopped = MicroDebugAdapter::ToString( AllThreadsStopped );

	return std::format(
		R"({{
			{},
			"event" : "continued",
			"body" : {{
				"threadId" : "{}",
				"allThreadsStopped" : "{}"
			}}
		}})", 
		header,
		ThreadID, 
		all_threads_stopped 
	);
}

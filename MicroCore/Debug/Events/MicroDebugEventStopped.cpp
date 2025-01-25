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
MicroDebugEventStopped::MicroDebugEventStopped( )
	: MicroDebugEventStopped{ MicroDebugEventReasons::None }
{ }

MicroDebugEventStopped::MicroDebugEventStopped( const MicroDebugEventReasons& reason )
	: MicroDebugEventStopped{ 0, 0, true, false, reason, "", "" }
{ }

MicroDebugEventStopped::MicroDebugEventStopped(
	const uint32_t hit_breakpoint_id,
	const bool preserve_focus_hint,
	const MicroDebugEventReasons& reason,
	const std::string& description,
	const std::string& text
)
	: MicroDebugEventStopped{
		0,
		hit_breakpoint_id,
		preserve_focus_hint,
		false,
		reason,
		description,
		text
	}
{ }

MicroDebugEventStopped::MicroDebugEventStopped(
	const uint32_t thread_id,
	const uint32_t hit_breakpoint_id,
	const bool preserve_focus_hint,
	const bool all_thread_stopped,
	const MicroDebugEventReasons& reason,
	const std::string& description,
	const std::string& text
)
	: MicroDebugEvent{ MicrDebugEventTypes::Stopped },
	ThreadID{ thread_id },
	HitBreakpointIds{ hit_breakpoint_id },
	PreserveFocusHint{ preserve_focus_hint },
	AllThreadsStopped{ all_thread_stopped },
	Reason{ reason },
	Description{ description },
	Text{ text }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroDebugEventStopped::GetIsValid( ) const {
	return Reason > MicroDebugEventReasons::None;
}

std::string MicroDebugEventStopped::ToString( ) const {
	const auto reason = micro::debug_reason_to_string( Reason );
	const auto preserve_focus_hint = micro::debug_bool_to_string( PreserveFocusHint );
	const auto all_threads_stopped = micro::debug_bool_to_string( AllThreadsStopped );

	return std::format( 
		R"({{
			"event" : "stopped",
			"body" : {{
				"reason" : "{}",
				"description" : "{}",
				"threadId" : "{}",
				"preserveFocusHint" : "{}",
				"text" : "{}",
				"allThreadsStopped" : "{}",
				"hitBreakpointIds" : "{}"
			}}
		}})",
		reason,
		Description,
		ThreadID,
		preserve_focus_hint,
		Text,
		all_threads_stopped,
		HitBreakpointIds
	);
}

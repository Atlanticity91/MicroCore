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
namespace micro {

	std::string debug_bool_to_string( const bool value ) {
		return value ? "true" : "false";
	}

	constexpr std::string debug_reason_to_string( const MicroDebugEventReasons reason ) {
		switch ( reason ) {
			// STOPPED
			case MicroDebugEventReasons::Step				   : return "step";
			case MicroDebugEventReasons::Breakpoint			   : return "breakpoint";
			case MicroDebugEventReasons::Exception			   : return "exception";
			case MicroDebugEventReasons::Pause				   : return "pause";
			case MicroDebugEventReasons::Entry				   : return "entry";
			case MicroDebugEventReasons::Goto				   : return "goto";
			case MicroDebugEventReasons::FunctionBreakpoint	   : return "function breakpoint";
			case MicroDebugEventReasons::DataBreakpoint		   : return "data breakpoint";
			case MicroDebugEventReasons::InstructionBreakpoint : return "instruction breakpoint";

			// BREAKPOINT
			case MicroDebugEventReasons::Changed			   : return "changed";
			case MicroDebugEventReasons::New				   : return "new";
			case MicroDebugEventReasons::Removed			   : return "removed";

			// THREAD
			case MicroDebugEventReasons::Started			   : return "started";
			case MicroDebugEventReasons::Exited				   : return "exited";

			default : break;
		}

		return "none";
	}

};

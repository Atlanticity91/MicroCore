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

#include "MicroWork.h"

/**
 * MicroWorkPriorities enum class
 * @note : Defined work priorities.
 **/
enum class MicroWorkPriorities : uint32_t { 

	MWP_HIGH = 0,
	MWP_LOW,

	MWP_COUNT

};

/**
 * MicroWorkManager class
 * @note : Represent work manager for multithreading.
 **/
class MicroWorkManager {

private:
	std::mutex m_mutex;
	std::queue<MicroWork> m_works[ 2 ];
	std::vector<std::thread> m_workers;
	bool m_can_work;

public:
	/**
	 * Constructor
	 **/
	MicroWorkManager( );

	/**
	 * Destructor
	 **/
	~MicroWorkManager( ) = default;

	/**
	 * Create function
	 * @note : Create the manager and threads for dispatch.
	 **/
	bool Create( );

	/**
	 * PushWork procedure
	 * @note : Push work for execution.
	 * @param priority : Priority ot the work.
	 * @param work : Work handle instance.
	 **/
	void PushWork( MicroWorkPriorities priority, const MicroWork& work );

	/**
	 * Destroy procedure
	 * @note : Terminate and clear threads.
	 **/
	void Destroy( );

private:
	/**
	 * WorkExecution static procedure
	 * @note : Thread "main" function for executing work.
	 * @param work_manager : Current MicroWorkManager instance.
	 **/
	static void WorkExecution( MicroWorkManager* work_manager );

public:
	/**
	 * GetCanWork const function
	 * @note : Get if a worker can execute work task.
	 **/
	bool GetCanWork( );

	/**
	 * GetCount const function
	 * @note : Get current thread count.
	 **/
	uint32_t GetCount( ) const;

	/**
	 * PopWork function
	 * @note : Pop first work task to available for execution.
	 * @param work : Reference for the work.
	 * @return : True if the function populate the work reference.
	 **/
	bool PopWork( MicroWork& work );

};

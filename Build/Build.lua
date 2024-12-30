--- TOOL INCLUDES
include "Premake/CSExtensions.lua"
include "Premake/VSExtensions.lua"
include "Build-Dependencies.lua"

--- PROJECT CONFIGURATION
workspace "Micro Solution"
	architecture "x64"
	startproject "MicroCore"
	location "../"
	configurations { 
		"Debug", 
		"Release", 
		"Dist" 
	}

	--- GLOBAL FLAGS
	flags "MultiProcessorCompile"
	
	--- WINDOWS
	filter "system:windows"
		-- WORKSPACE-WIDE BUILD OPTIONS FOR MSVC
		buildoptions { 
			"/EHsc", 
			"/Zc:preprocessor", 
			"/Zc:__cplusplus" 
		}

	--- THIRDPARTY PROJECTS
	group "Thirdparty"
		include "Thirdparty/Build-Header-Glm.lua"
		include "Thirdparty/Build-Header-Libclang.lua"
		include "Thirdparty/Build-Header-Spdlog.lua"
		include "Thirdparty/Build-Yaml.lua"
	--- TEST PROJECTS
	group "Test"
		include "Test/Build-MicroTest.lua"
	group ""

	--- MAIN PROJECT
	include "Build-MicroCore.lua"

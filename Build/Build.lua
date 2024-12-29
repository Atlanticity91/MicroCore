include "Premake/CSExtensions.lua"
include "Premake/VSExtensions.lua"
include "Build-Dependencies.lua"

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
	
	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { 
			"/EHsc",
			"/Zc:preprocessor", 
			"/Zc:__cplusplus" 
		}

	--- Thirdparty Projects
	group "Thirdparty"
		include "Thirdparty/Build-Header-Glm.lua"
		include "Thirdparty/Build-Header-Libclang.lua"
		include "Thirdparty/Build-Header-Spdlog.lua"
		include "Thirdparty/Build-Yaml.lua"

	--- Test Projects
	group "Test"
		include "Test/Build-MicroTest.lua"
	group ""

	--- Main Project
	include "Build-MicroCore.lua"

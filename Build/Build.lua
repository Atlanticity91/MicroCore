workspace "MicroCore"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "MicroCore"
	location "../"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	group "Thirdparty"
		include "Build-Spdlog.lua"
		include "Build-GLM.lua"
		include "Build-Yaml.lua"
		include "Build-Libssh2.lua"
		include "Build-Libgit2.lua"
	group ""

	include "Build-MicroCore.lua"

--- GLM PROJECT
project "GLM"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files { 
		"%{IncludeDirs.Glm}/glm/**.h", 
		"%{IncludeDirs.Glm}/glm/**.hpp" 
	}

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

--- LIBCLANG PROJET
project "libclang"
	kind "StaticLib"
	language "C"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files "%{IncludeDirs.Libclang}/clang-c/**.h"

	--- WINDOWS
	filter "system:windows"
		cdialect "C17"

--- SPDLOG PROJECT
project "Spdlog"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files "%{IncludeDirs.Spdlog}/include/spdlog/**.h"

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

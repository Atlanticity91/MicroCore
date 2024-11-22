--- GLM PROJECT
project "GLM"
	kind "StaticLib"
	language "C++"
	location "%{wks.location}/Solution/"

	files { 
		"%{IncludeDirs.glm}/glm/**.h", 
		"%{IncludeDirs.glm}/glm/**.hpp" 
	}

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

--- LIBCLANG PROJET
project "libclang"
	kind "StaticLib"
	language "C"
	location "%{wks.location}/Solution/"

	files "%{IncludeDirs.libclang}/clang-c/**.h"

	--- WINDOWS
	filter "system:windows"
		cdialect "C17"

--- SPDLOG PROJECT
project "Spdlog"
	kind "StaticLib"
	language "C++"
	location "%{wks.location}/Solution/"

	files "%{IncludeDirs.spdlog}/include/spdlog/**.h"

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

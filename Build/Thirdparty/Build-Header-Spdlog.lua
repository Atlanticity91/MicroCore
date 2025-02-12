project "Spdlog"
	kind "Utility"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files "%{IncludeDirs.Spdlog}include/spdlog/**.h"

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

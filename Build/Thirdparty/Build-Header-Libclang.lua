project "libclang"
	kind "StaticLib"
	language "C"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files "%{IncludeDirs.Libclang}/clang-c/**.h"

	--- WINDOWS
	filter "system:windows"
		cdialect "C17"

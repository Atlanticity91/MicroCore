project "GLM"
	kind "Utility"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- GLOBAL SOURCE FILES
	files { 
		"%{IncludeDirs.Glm}glm/**.h", 
		"%{IncludeDirs.Glm}glm/**.hpp" 
	}

	--- WINDOWS
	filter "system:windows"
		cppdialect "C++20"

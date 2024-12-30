project "Yaml"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs "%{IncludeDirs.Yaml}include/"
	externalincludedirs "%{IncludeDirs.Yaml}include/"

	--- GLOBAL DEFINES
	defines "YAML_CPP_STATIC_DEFINE"

	--- GLOBAL FILES
	files { 
		"%{IncludeDirs.Yaml}src/**.h",
		"%{IncludeDirs.Yaml}src/**.cpp"
	}

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "off"

		--- WINDOWS SPECIFIC DEFINE
		defines "WINDOWS"

	--- CONFIGURATION
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

		--- DEFINE
		defines { "DEBUG" }

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

		--- DEFINE
		defines { "RELEASE" }

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
		symbols "Off"

		--- DEFINE
		defines { "DIST" }

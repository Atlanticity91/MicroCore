project "Yaml"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}/%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs "%{IncludeDirs.Yaml}/include/"
	externalincludedirs "%{IncludeDirs.Yaml}/include/"

	--- GLOBAL DEFINES
	defines "YAML_CPP_STATIC_DEFINE"

	--- GLOBAL FILES
	files { 
		"%{IncludeDirs.Yaml}/src/**.h",
		"%{IncludeDirs.Yaml}/src/**.cpp"
	}

	--- CONFIGURATION
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		defines "WINDOWS"
		cppdialect "C++20"
		staticruntime "off"

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

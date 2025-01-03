project "MicroCore"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs {
		"%{IncludeDirs.MicroCore}",
		"%{IncludeDirs.Glm}",
		"%{IncludeDirs.Libclang}",
		"%{IncludeDirs.Spdlog}include/",
		"%{IncludeDirs.Yaml}include/"
	}

	externalincludedirs { 
		"%{IncludeDirs.MicroCore}",
		"%{IncludeDirs.Glm}",
		"%{IncludeDirs.Libclang}",
		"%{IncludeDirs.Spdlog}include/",
		"%{IncludeDirs.Yaml}include/"
	}

	--- PRECOMPILED HEADERS
	pchheader "__micro_core_pch.h"

	--- GLOBAL SOURCE FILES
	files {
		"%{IncludeDirs.MicroCore}**.h",
		"%{IncludeDirs.MicroCore}**.cpp" 
	}

	--- GLOBAL LINKS
	links "Yaml"

	--- LINUX
	filter "system:linux"
		systemversion "latest"

		--- LINUX SPECIFIC DEFINES
		defines { "LINUX" }

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "off"
		
		--- WINDOWS SPECIFIC DEFINES
		defines { 
			"WINDOWS",
			"_CRT_SECURE_NO_WARNINGS" 
		}
		
		--- PRECOMPILED HEADERS
		pchsource "../MicroCore/__micro_core_pch.cpp"

		--- WINDOWS SPECIFIC PRE-BUILD COMMAND
		prebuildmessage "Copy Libclang"
		prebuildcommands  {
			"{COPYFILE} %{IncludeDirs.Libclang}windows/libclang.lib %{OutputDirs.Bin}%{cfg.buildcfg}/",
			"{COPYFILE} %{IncludeDirs.Libclang}windows/libclang.dll %{OutputDirs.Bin}%{cfg.buildcfg}/"
		}

		--- WINDOWS SPECIFIC LINK
		links "%{OutputDirs.Bin}%{cfg.buildcfg}/libclang.lib"

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

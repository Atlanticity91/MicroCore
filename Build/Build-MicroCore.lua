project "MicroCore"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}/%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs {
		"%{IncludeDirs.MicroCore}",
		"%{IncludeDirs.Glm}",
		"%{IncludeDirs.Libclang}",
		"%{IncludeDirs.Spdlog}/include/",
		"%{IncludeDirs.Yaml}/include/"
	}

	externalincludedirs { 
		"%{IncludeDirs.MicroCore}",
		"%{IncludeDirs.Glm}",
		"%{IncludeDirs.Libclang}",
		"%{IncludeDirs.Spdlog}/include/",
		"%{IncludeDirs.Yaml}/include/"
	}

	--- PRECOMPILED HEADERS
	pchheader "__micro_core_pch.h"

	--- GLOBAL SOURCE FILES
	files {
		"%{IncludeDirs.MicroCore}/**.h",
		"%{IncludeDirs.MicroCore}/**.cpp" 
	}

	--- GLOBAL LINKS
	links "Yaml"

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
		cppdialect "C++20"
		staticruntime "off"
		
		--- DEFINES
		defines { 
			"WINDOWS",
			"_CRT_SECURE_NO_WARNINGS" 
		}
		
		--- PRECOMPILED HEADERS
		pchsource "../MicroCore/__micro_core_pch.cpp"

		--- POST BUILD
		postbuildcommands {
			"{COPYFILE} %{IncludeDirs.Libclang}windows/libclang.lib %{OutputDirs.Bin}%{cfg.buildcfg}/",
			"{COPYFILE} %{IncludeDirs.Libclang}windows/libclang.dll %{OutputDirs.Bin}%{cfg.buildcfg}/"
		}

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

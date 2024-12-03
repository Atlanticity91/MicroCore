project "MicroCore"
	kind "StaticLib"
	language "C++"

	files {
		"../MicroCore/**.h",
		"../MicroCore/**.cpp" 
	}

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	debugdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	includedirs {
		"%{wks.location}/MicroCore/",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.libclang}",
		"%{IncludeDirs.spdlog}/include/",
		"%{IncludeDirs.yaml}/include/"
	}
	externalincludedirs { 
		"%{wks.location}/MicroCore/",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.libclang}",
		"%{IncludeDirs.spdlog}/include/",
		"%{IncludeDirs.yaml}/include/"
	}

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
		
		defines { 
			"WINDOWS",
			"_CRT_SECURE_NO_WARNINGS" 
		}
		
		pchheader "__micro_core_pch.h"
		pchsource "../MicroCore/__micro_core_pch.cpp"

		postbuildcommands {
			"{COPYFILE} %{IncludeDirs.libclang}/windows/libclang.lib bin/%{cfg.buildcfg}/",
			"{COPYFILE} %{IncludeDirs.libclang}/windows/libclang.dll bin/%{cfg.buildcfg}/"
		}

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

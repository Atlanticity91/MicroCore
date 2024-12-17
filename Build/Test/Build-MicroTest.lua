project "MicroTest"
	kind "SharedLib"
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

	--- GLOBAL LINKS
	links { "Yaml", "MicroCore" }

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

		--- SOURCES FILES
		files {
			"%{IncludeDirs.MicroTest}/windows/**.h",
			"%{IncludeDirs.MicroTest}/windows/**.cpp"
		}

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

		--- SOURCES FILESs
		files {
			"%{IncludeDirs.MicroTest}/linux/**.h",
			"%{IncludeDirs.MicroTest}/linux/**.cpp"
		}

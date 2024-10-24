project "MicroCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files { "../MicroCore/**.h", "../MicroCore/**.cpp" }

	targetdir "%{wks.location}/bin/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	links { "Yaml" }

	includedirs {
		"%{wks.location}/MicroCore/",
		"%{wks.location}/Thirdparty/glm/",
		"%{wks.location}/Thirdparty/spdlog/include/",
		"%{wks.location}/Thirdparty/yaml-cpp/include/"
	}
	externalincludedirs { 
		"%{wks.location}/MicroCore/",
		"%{wks.location}/Thirdparty/glm/",
		"%{wks.location}/Thirdparty/spdlog/include/",
		"%{wks.location}/Thirdparty/yaml-cpp/include/"
	}

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }
		flags { "MultiProcessorCompile" }

		pchheader "__micro_core_pch.h"
		pchsource "../MicroCore/__micro_core_pch.cpp"

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }
	
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

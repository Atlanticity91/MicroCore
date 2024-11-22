project "Libssh2"
	kind "StaticLib"
	language "C"
	location "%{wks.location}/Solution/"

	files ""

	includedirs ""

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		cdialect "C17"
		staticruntime "off"
		defines "WINDOWS"

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

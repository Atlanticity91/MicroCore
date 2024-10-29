project "Libssh2"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	staticruntime "off"
	location "../Solution/"

	defines { "" }

	files { 
		"../Thirdparty/yaml-cpp/src/**.h",
		"../Thirdparty/yaml-cpp/src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Thirdparty/yaml-cpp/include/"
	}

	targetdir "%{wks.location}/bin/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }
		flags { "MultiProcessorCompile" }

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

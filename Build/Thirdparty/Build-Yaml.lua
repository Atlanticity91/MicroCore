project "Yaml"
	kind "StaticLib"
	language "C++"
	location "%{wks.location}/Solution/"

	defines "YAML_CPP_STATIC_DEFINE"

	files { 
		"%{IncludeDirs.yaml}/src/**.h",
		"%{IncludeDirs.yaml}/src/**.cpp"
	}

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	includedirs "%{wks.location}/Thirdparty/yaml-cpp/include/"

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

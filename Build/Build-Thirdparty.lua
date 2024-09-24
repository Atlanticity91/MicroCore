project "glm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	location "../Thirdparty/"

	files { 
		"../Thirdparty/glm/glm/**.h", 
		"../Thirdparty/glm/glm/**.hpp" 
	}

project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	location "../Thirdparty/"

	files { "../Thirdparty/spdlog/include/spdlog/**.h" }

project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"
    location "../Thirdparty/"

    defines { "YAML_CPP_STATIC_DEFINE" }

    files { 
    	"../Thirdparty/yaml-cpp/src/**.h",
    	"../Thirdparty/yaml-cpp/src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Thirdparty/yaml-cpp/include/"
	}

	targetdir "%{wks.location}/bin/"
	objdir "%{wks.location}/bin-int/%{prj.name}"

	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }
		flags { "MultiProcessorCompile" }

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

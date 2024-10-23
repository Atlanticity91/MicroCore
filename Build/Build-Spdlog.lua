project "Spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	location "../Solution/"

	files { "../Thirdparty/spdlog/include/spdlog/**.h" }

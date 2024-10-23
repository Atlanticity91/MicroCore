project "GLM"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	location "../Solution/"

	files { 
		"../Thirdparty/glm/glm/**.h", 
		"../Thirdparty/glm/glm/**.hpp" 
	}

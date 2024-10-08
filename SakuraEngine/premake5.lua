project "SakuraEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/" .. outputbindir .. "/%{prj.name}")
	objdir ("%{wks.location}/" .. outputintdir .. "/%{prj.name}")

	pchheader "skrpch.h"
	pchsource "src/skrpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SKR_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "SKR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SKR_RELEASE"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines "SKR_DIST"
		runtime "Release"
		optimize "On"
		symbols "Off"
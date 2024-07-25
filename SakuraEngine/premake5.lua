project "SakuraEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/" .. outputbindir .. "/%{prj.name}")
	objdir ("%{wks.location}/" .. outputintdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		defines "SKR_PLATFORM_WINDOWS"

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
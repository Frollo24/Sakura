project "SakuraSandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/" .. outputbindir .. "/%{prj.name}")
	objdir ("%{wks.location}/" .. outputintdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src/",
		"%{wks.location}/SakuraEngine/src/",
		"%{wks.location}/SakuraEngine/vendor/spdlog/include",
		"%{IncludeDir.glm}"
	}

	links
	{
		"SakuraEngine"
	}

	postbuildcommands
	{
		"{COPYDIR} \"%{prj.location}assets\" \"%{wks.location}/" .. outputbindir .. "/%{prj.name}/assets" .. "/\""
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		defines "SKR_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "SKR_DEBUG"
		runtime "Debug"
		symbols "On"
		postbuildcommands {
			"{COPYFILE} %[%{wks.location}/SakuraEngine/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll] %[%{wks.location}/" .. outputbindir .. "/%{prj.name}/assimp-vc143-mtd.dll]",
		}

	filter "configurations:Release"
		defines "SKR_RELEASE"
		runtime "Release"
		optimize "On"
		symbols "On"
		postbuildcommands {
			"{COPYFILE} %[%{wks.location}/SakuraEngine/vendor/assimp/bin/Release/assimp-vc143-mt.dll] %[%{wks.location}/" .. outputbindir .. "/%{prj.name}/assimp-vc143-mt.dll]",
		}

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "SKR_DIST"
		runtime "Release"
		optimize "On"
		symbols "Off"
		postbuildcommands {
			"{COPYFILE} %[%{wks.location}/SakuraEngine/vendor/assimp/bin/Release/assimp-vc143-mt.dll] %[%{wks.location}/" .. outputbindir .. "/%{prj.name}/assimp-vc143-mt.dll]",
		}
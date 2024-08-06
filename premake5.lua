include "dependencies.lua"

workspace "Sakura"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
outputbindir = "Build/Binaries/%{cfg.buildcfg}-%{cfg.architecture}"
outputintdir = "Build/Intermediates/%{cfg.buildcfg}-%{cfg.architecture}"

group "Dependencies"
	include "SakuraEngine/vendor/GLFW"
	include "SakuraEngine/vendor/Glad"
group ""

include "SakuraEngine"
include "SakuraSandbox"

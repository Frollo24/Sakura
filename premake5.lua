workspace "Sakura"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputbindir = "Build/Binaries/%{cfg.buildcfg}-%{cfg.architecture}"
outputintdir = "Build/Intermediates/%{cfg.buildcfg}-%{cfg.architecture}"

include "SakuraEngine"
include "SakuraSandbox"

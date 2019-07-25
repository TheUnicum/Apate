workspace "Apate"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Apate/vendor/GLFW/include"

include "Apate/vendor/GLFW"

project "Apate"
    location "Apate"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
    }

    -- The contents of the %{} are run through loadstring()
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
    }

    links
    {
        "GLFW",
        "opengl32.lib",
    }

    pchheader "APpch.h"
    pchsource "Apate/src/APpch.cpp"
    filter "files:**.c"
        flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AP_PLATFORM_WINDOWS",
            "AP_BUILD_DLL",
        }

    filter "configurations:Debug"
        defines "AP_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AP_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AP_DIST"
        runtime "Release"
        optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Apate/vendor/spdlog/include",
        "Apate/src",
    }

    links
    {
        "Apate",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AP_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "AP_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AP_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AP_DIST"
        runtime "Release"
        optimize "on"

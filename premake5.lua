-- premake setup
print("[premake] generating project files...")

workspace "eclipse"
  startproject "eclipseeditor"
  architecture "ARM64"

  configurations
  {
    "Debug",
    "Release"
  }

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

-- External Dependencies
externals = {}
externals["spdlog"] = "external/spdlog"
externals["glad"] = "external/glad"

project "eclipse"
    location "eclipse"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "src/**.h",
        "src/**.cpp",
        "core/**.h",
        "core/**.cpp",
        "managers/**.h",
        "managers/**.cpp",
        "graphics/**.h",
        "graphics/**.cpp",
        "external/glad/src/glad.c"
    }

    removefiles
    {
        "src/main.cpp"
    }

    includedirs
    {
        "src",
        "core",
        "managers",
        "graphics",
        "/opt/homebrew/include",
        "%{externals.spdlog}/include",
        "%{externals.glad}/include"
    }

    fatalwarnings {}

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"
        defines
        {
            "ECLIPSE_PLATFORM_WINDOWS"
        }

    filter {"system:macosx", "configurations:*"}
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            "ECLIPSE_PLATFORM_MAC"
        }

    filter {"system:linux", "configurations:*"}
        defines
        {
            "ECLIPSE_PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        defines
        {
            "ECLIPSE_CONFIG_DEBUG",
            "DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "ECLIPSE_CONFIG_RELEASE",
            "NDEBUG"
        }
        runtime "Release"
        symbols "off"
        optimize "on"

project "eclipseeditor"
    location "eclipseeditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    links "eclipse"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "src/main.cpp"
    }

    includedirs
    {
        "src",
        "core",
        "managers",
        "/opt/homebrew/include",
        "%{externals.spdlog}/include",
        "%{externals.glad}/include"
    }

    fatalwarnings {}

    filter {"system:windows", "configurations:*"}
        systemversion "latest"
        defines
        {
            "ECLIPSE_PLATFORM_WINDOWS"
        }

        links
        {
            "SDL2"
        }

    filter {"system:macosx", "configurations:*"}
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            "ECLIPSE_PLATFORM_MAC"
        }

        libdirs
        {
            "/opt/homebrew/lib"
        }

        links
        {
            "SDL2",
            "SDL2main"
        }

        linkoptions
        {
            "-Wl,-framework,Cocoa"
        }

    filter {"system:linux", "configurations:*"}
        defines
        {
            "ECLIPSE_PLATFORM_LINUX"
        }

        links
        {
            "SDL2",
            "dl"
        }

    filter "configurations:Debug"
        defines
        {
            "ECLIPSE_CONFIG_DEBUG",
            "DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "ECLIPSE_CONFIG_RELEASE",
            "NDEBUG"
        }
        runtime "Release"
        symbols "off"
        optimize "on"

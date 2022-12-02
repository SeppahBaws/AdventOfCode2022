project "AdventOfCode"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    warnings "extra"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pch.h"
    pchsource "src/pch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.fmt}"
    }

    links
    {
        "fmt"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

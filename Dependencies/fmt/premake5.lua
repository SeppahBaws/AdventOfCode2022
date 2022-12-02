project "fmt"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "src/**.cc"
    }

    includedirs
    {
        "include"
    }

    filter "files:**.cc"
        compileas "Module"

    filter "files:**.h"
        compileas "HeaderUnit"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


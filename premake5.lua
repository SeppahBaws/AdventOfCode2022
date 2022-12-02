workspace "AdventOfCode2022"
    architecture "x86_64"
    startproject "Puzzles"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile",
        "FatalWarnings"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["fmt"] = "%{wks.location}/Dependencies/fmt/include"

group "Dependencies"
    include "Dependencies/fmt"
group ""

include "AdventOfCode"

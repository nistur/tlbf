solution "tlbf"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLBF_BUILD" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tlbf"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

project "tlbf-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
targetname "tlbf"

project "tlbf-interpreter"
targetname "tlbf"
kind "ConsoleApp"
files { "interpreter/**.c" }
links { "tlbf" }

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tlbf" }
configuration "Debug"
--postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")

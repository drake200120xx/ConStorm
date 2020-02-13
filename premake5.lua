workspace "ConStorm"
	configurations { "Debug", "Release" }
	platforms { "Win32", "x64" }
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

cons_include = "%{wks.location}/ConStorm/cons"
sandbox_lib = "%{wks.location}Sandbox/lib/"
bin_output = "%{prj.location}/bin/%{cfg.buildcfg}-%{cfg.architecture}/"
obj_output = "%{prj.location}/obj/%{cfg.buildcfg}-%{cfg.architecture}/"


project "ConStorm"
	kind "StaticLib"
	language "C++"
	location "ConStorm"
	files {
		"%{prj.location}/cons/**.h",
		"%{prj.location}/cons/**.hpp",
		"%{prj.location}/cons/**.cpp",
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.cpp"
	}
	targetdir (bin_output)
	objdir (obj_output)
	includedirs {
		"%{prj.location}/cons"
	}
	
	postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} \"" .. sandbox_lib .. "\"")
	}
	
	filter "configurations:Debug" 
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release" 
		optimize "On"

	filter "platforms:Win32" 
		system "Windows"
		architecture "x32"

	filter "platforms:x64"
		system "Windows"
		architecture "x64"


project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"
	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.cpp"
	}
	targetdir (bin_output)
	objdir (obj_output)
	includedirs {
		(cons_include)
	}
	links { "ConStorm" }

	filter "configurations:Debug" 
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release" 
		optimize "On"

	filter "platforms:Win32" 
		system "Windows"
		architecture "x32"

	filter "platforms:x64"
		system "Windows"
		architecture "x64"


solution "VirtualAwesome"
  configurations { "Debug", "Release" }
	defines { "OSG_LIBRARY_STATIC" }
	language "C++"

	configuration "Debug"
    defines { "DEBUG" }
    flags { "Symbols" }
		
  configuration "Release"
    defines { "RELEASE" }
    flags { "Optimize" }


	configuration { "macosx" }
		platforms "x32"
		buildoptions {
			"-Wall", "-Wparentheses", "-Wno-long-long", "-Wno-import", "-pedantic",
			"-Wreturn-type", "-Wmissing-braces", "-Wunknown-pragmas", "-Wunused",
			"-mmacosx-version-min=10.6", "-ftree-vectorize", 
			"-fvisibility-inlines-hidden"
		}

	-- configuration { "linux" }	

	configuration { "windows" }
		defines { "WIN32", "TARGET_WIN32" }


if _ACTION == "clean" then
  os.rmdir("VirtualAwesome.ncb")
  os.rmdir("VirtualAwesome.sln")
end


-- ------ va ------------------------------------------------------------------

if os.is("macosx") then
	va_include_dirs = { "/Developer/Headers/FlatCarbon", "libs/osg-osx/include", "core/va/include" }
	va_link_dirs = { "libs/freetype-osx/lib", "libs/osg-osx/lib" }
  va_link_libs = { 
		"AGL.framework", "ApplicationServices.framework", 
		"AudioToolbox.framework", "Cocoa.framework", "Carbon.framework", 
		"CoreAudio.framework", "CoreFoundation.framework", 
		"CoreServices.framework", "OpenGL.framework", "QuickTime.framework", 
		"IOKit.framework", "freetype","osgViewer",	"osgdb_freetype",	"osgdb_qt",
		"osgdb_bmp", "osgdb_osg",	"osgdb_obj", "osgdb_3ds", "osgdb_dxf",
		"osgdb_stl", "osgGA",	"osgText", "osgDB",	"osgUtil", "osg",	"OpenThreads"	
 }
end	
	
if os.is("linux") then
	va_include_dirs = { "libs/osg-linux/include", "core/va/include" }
	va_link_dirs = { "libs/osg-linux/lib" }		
  va_link_libs = { 
		"pthread", "m", "GL", "GLU", "SM", "ICE", "X11", "Xext", "Xrandr", "z",
		"freetype", "jpeg", "png", "osgViewer", "osgdb_freetype", "osgdb_png",
		"osgdb_jpeg", "osgdb_bmp", "osgdb_osg", "osgdb_obj", "osgdb_3ds", 
		"osgdb_dxf", "osgdb_stl", "osgGA", "osgText", "osgDB", "osgUtil", "osg",
		"OpenThreads"	
 }
end	
	
if os.is("windows") then
	va_include_dirs = { "libs/osg-win32/include", "core/va/include" }
	va_link_dirs = { 
		"libs/freetype-win32/lib",
		"libs/jpeg-win32/lib",
		"libs/png-win32/lib",
		"libs/zlib-win32/lib",
		"libs/osg-win32/lib"
	}				
  va_link_libs = {
		"OpenGL32", "GLu32", "kernel32", "setupapi", "user32", "gdi32",
		"winspool", "comdlg32", "advapi32", "shell32", "ole32", "oleaut32", "uuid",
		"freetype2311_D", "jpegD", "libpng12_staticd", "zlibD", 
		"osg55-osgViewerd", "osgdb_freetyped", "osgdb_pngd", "osgdb_jpegd", 
		"osgdb_bmpd", "osgdb_osgd", "osgdb_objd", "osgdb_3dsd", "osgdb_dxfd",
		"osgdb_stld", "osg55-osgGAd", "osg55-osgTextd", "osg55-osgDBd", 
		"osg55-osgUtild", "osg55-osgd", "ot11-OpenThreadsd"			
	}
end


project "va"
	kind "StaticLib"
	location "core/va"
	files { "core/va/include/va/*.h", "core/va/src/*.cpp" }
	includedirs { va_include_dirs }
	
  configuration "Debug"
    targetdir "core/va/bin/debug"
 
  configuration "Release"
    targetdir "core/va/bin/release"	


if _ACTION == "clean" then
  os.rmdir("core/va/bin")
  os.rmdir("core/va/obj")
	os.rmdir("core/va/va.xcodeproj")
	os.rmdir("core/va/va.vcproj")
end

-- ------ va end --------------------------------------------------------------



-- ------ vaMice --------------------------------------------------------------

va_mice_include_dirs = { "addons/vaMice/include", "addons/vaMice/libs/manymouse" }
va_mice_link_dirs = { }
va_mice_link_libs = { }

		
project "vaMice"
	kind "StaticLib"
	location "addons/vaMice"
	files { 
		"addons/vaMice/include/vaMice/*.h", 
		"addons/vaMice/src/*.cpp", 
		"addons/vaMice/libs/manymouse/*.h",
		"addons/vaMice/libs/manymouse/*.c"
	}
	includedirs { va_include_dirs, va_mice_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaMice/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaMice/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaMice/bin")
  os.rmdir("addons/vaMice/obj")
	os.rmdir("addons/vaMice/vaMice.xcodeproj")
	os.rmdir("addons/vaMice/vaMice.vcproj")
end

-- ------ vaMice end ----------------------------------------------------------



-- ------ vaMultipad ----------------------------------------------------------

if os.is("macosx") then
	va_multipad_include_dirs = { "addons/vaMultipad/include" }
	va_multipad_link_dirs = { }
	-- va_multipad_link_dirs = { os.findlib("MultitouchSupport") }
	va_multipad_link_libs = { "/System/Library/PrivateFrameworks/MultitouchSupport.framework" }

		
	project "vaMultipad"
		kind "StaticLib"
		location "addons/vaMultipad"
		files { "addons/vaMultipad/include/vaMultipad/*.h", "addons/vaMultipad/src/*.cpp" }
		includedirs { va_include_dirs, va_multipad_include_dirs }
	
	  configuration "Debug"
	    targetdir "addons/vaMultipad/bin/debug"
 
	  configuration "Release"
	    targetdir "addons/vaMultipad/bin/release"	
end


if _ACTION == "clean" then
  os.rmdir("addons/vaMultipad/bin")
  os.rmdir("addons/vaMultipad/obj")
	os.rmdir("addons/vaMultipad/vaMultipad.xcodeproj")
	os.rmdir("addons/vaMultipad/vaMultipad.vcproj")
end

-- ------ vaMultipad end ------------------------------------------------------



-- ------ vaNetwork -----------------------------------------------------------

va_network_include_dirs = { "addons/vaNetwork/include" }

if os.is("macosx") or os.is("linux") then
	va_network_link_dirs = { }
  va_network_link_libs = { }
end
	
if os.is("windows") then
	va_network_link_dirs = { }				
  va_network_link_libs = { "ws2_32" }
end
		
		
project "vaNetwork"
	kind "StaticLib"
	location "addons/vaNetwork"
	files { 
		"addons/vaNetwork/include/vaNetwork/*.h",
		"addons/vaNetwork/src/*.cpp",
		"addons/vaNetwork/include/vaNetwork/Utf.inl"
	}
	includedirs { va_include_dirs, va_network_include_dirs }
	
  configuration { "macosx or linux" }
		excludes { 
			"addons/vaNetwork/include/vaNetwork/SocketImplWin32.h", 
			"addons/vaNetwork/src/SocketImplWin32.cpp"
		}
		
  configuration { "windows" }
		excludes { 
			"addons/vaNetwork/include/vaNetwork/SocketImplUnix.h", 
			"addons/vaNetwork/src/SocketImplUnix.cpp"
		}
	
  configuration "Debug"
    targetdir "addons/vaNetwork/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaNetwork/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaNetwork/bin")
  os.rmdir("addons/vaNetwork/obj")
	os.rmdir("addons/vaNetwork/vaNetwork.xcodeproj")
	os.rmdir("addons/vaNetwork/vaNetwork.vcproj")
end

-- ------ vaNetwork end -------------------------------------------------------



-- ------ vaOpenal ------------------------------------------------------------

if os.is("macosx") then
	va_openal_include_dirs = { "addons/vaOpenal/include", "addons/vaOpenal/libs/sndfile-osx/include" }
	va_openal_link_dirs = { "addons/vaOpenal/libs/sndfile-osx/lib" }
  va_openal_link_libs = { "OpenAL.framework", "sndfile" }
end	
	
if os.is("linux") then
	va_openal_include_dirs = { "addons/vaOpenal/include", "addons/vaOpenal/libs/sndfile-linux/include" }
	va_openal_link_dirs = { "addons/vaOpenal/libs/sndfile-linux/lib" }		
  va_openal_link_libs = { "asound", "openal", "sndfile" }
end	
	
if os.is("windows") then
	va_openal_include_dirs = { "addons/vaOpenal/include", "addons/vaOpenal/libs/openal-win32/include", "addons/vaOpenal/libs/sndfile-win32/include" }
	va_openal_link_dirs = { "addons/vaOpenal/libs/openal-win32/lib", "addons/vaOpenal/libs/sndfile-win32/lib" }				
  va_openal_link_libs = { "OpenAL32", "sndfile-1" }
end
		
		
project "vaOpenal"
	kind "StaticLib"
	location "addons/vaOpenal"
	files { "addons/vaOpenal/include/vaOpenal/*.h", "addons/vaOpenal/src/*.cpp", "addons/vaOpenal/src/stb_vorbis.c" }
	includedirs { va_include_dirs, va_openal_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaOpenal/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaOpenal/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaOpenal/bin")
  os.rmdir("addons/vaOpenal/obj")
	os.rmdir("addons/vaOpenal/vaOpenal.xcodeproj")
	os.rmdir("addons/vaOpenal/vaOpenal.vcproj")
end

-- ------ vaOpenal end --------------------------------------------------------



-- ------ vaOpencv ------------------------------------------------------------

if os.is("macosx") then
	va_opencv_include_dirs = { "addons/vaOpencv/include", "addons/vaOpencv/libs/opencv-osx/include" }
	va_opencv_link_dirs = { "addons/vaOpencv/libs/opencv-osx/lib" }
  va_opencv_link_libs = { "OpenCV" }
end	
	
if os.is("linux") then
	va_opencv_include_dirs = { "addons/vaOpencv/include", "addons/vaOpencv/libs/opencv-linux/include" }
	va_opencv_link_dirs = { "addons/vaOpencv/libs/opencv-linux/lib" }		
  va_opencv_link_libs = { "cv", "cvaux", "cxcore" }
end	
	
if os.is("windows") then
	va_opencv_include_dirs = { "addons/vaOpencv/include", "addons/vaOpencv/libs/opencv-win32/include" }
	va_opencv_link_dirs = { "addons/vaOpencv/libs/opencv-win32/lib" }				
  va_opencv_link_libs = { "cv110d", "cvaux110d", "cxcore110d" }
end


project "vaOpencv"
	kind "StaticLib"
	location "addons/vaOpencv"
	files { "addons/vaOpencv/include/vaOpencv/*.h", "addons/vaOpencv/src/*.cpp" }
	includedirs { va_include_dirs, va_opencv_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaOpencv/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaOpencv/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaOpencv/bin")
  os.rmdir("addons/vaOpencv/obj")
	os.rmdir("addons/vaOpencv/vaOpencv.xcodeproj")
	os.rmdir("addons/vaOpencv/vaOpencv.vcproj")
end

-- ------ vaOpencv end --------------------------------------------------------



-- ------ vaOsc ---------------------------------------------------------------

va_osc_include_dirs = { "addons/vaOsc/include", "addons/vaOsc/libs/oscpack/include" }

if os.is("macosx") or os.is("linux") then
	va_osc_link_dirs = { }
  va_osc_link_libs = { }
end
	
if os.is("windows") then
	va_osc_link_dirs = { }				
  va_osc_link_libs = { "ws2_32.lib", "winmm.lib" }
end
		
		
project "vaOsc"
	kind "StaticLib"
	location "addons/vaOsc"
	files { 
		"addons/vaOsc/include/vaOsc/*.h",
		"addons/vaOsc/src/*.cpp",
		"addons/vaOsc/libs/oscpack/include/oscpack/*.h",
		"addons/vaOsc/libs/oscpack/src/*.cpp"
	}
	includedirs { va_include_dirs, va_osc_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaOsc/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaOsc/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaOsc/bin")
  os.rmdir("addons/vaOsc/obj")
	os.rmdir("addons/vaOsc/vaOsc.xcodeproj")
	os.rmdir("addons/vaOsc/vaOsc.vcproj")
end

-- ------ vaOsc end -----------------------------------------------------------



-- ------ vaSound -------------------------------------------------------------

va_sound_include_dirs = { "addons/vaSound/include", "addons/vaSound/libs/stk/include" }

if os.is("macosx") then
	va_sound_link_dirs = { }
  va_sound_link_libs = { "CoreMidi.framework" }
end

if os.is("linux") then
	va_sound_link_dirs = { }
  va_sound_link_libs = { "asound" }
end
	
if os.is("windows") then
	va_sound_link_dirs = { }				
  va_sound_link_libs = { "ws2_32.lib", "winmm.lib" }
end
		
		
project "vaSound"
	kind "StaticLib"
	location "addons/vaSound"
	files { 
		"addons/vaSound/include/vaSound/*.h",
		"addons/vaSound/src/*.cpp",
		"addons/vaSound/libs/stk/include/stk/*.h",
		"addons/vaSound/libs/stk/include/stk/*.msg",
		"addons/vaSound/libs/stk/include/stk/*.tbl",
		"addons/vaSound/libs/stk/src/*.cpp"
	}
	includedirs { va_include_dirs, va_sound_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaSound/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaSound/bin/release"

  configuration { "macosx" }
		defines { "__MACOSX_CORE__", "__LITTLE_ENDIAN__" }

  configuration { "linux" }
		defines { "__LINUX_ALSA__", "__LINUX_ALSASEQ__", "__LITTLE_ENDIAN__" }
		
  configuration { "windows" }
		defines { "__WINDOWS_DS__", "__WINDOWS_MM__", "__LITTLE_ENDIAN__" }


if _ACTION == "clean" then
  os.rmdir("addons/vaSound/bin")
  os.rmdir("addons/vaSound/obj")
	os.rmdir("addons/vaSound/vaSound.xcodeproj")
	os.rmdir("addons/vaSound/vaSound.vcproj")
end

-- ------ vaSound end ---------------------------------------------------------



-- ------ vaTouchkit ----------------------------------------------------------

if os.is("macosx") then
	va_touchkit_include_dirs = { "addons/vaTouchkit/include", "addons/vaTouchkit/libs/dc1394-osx/include" }
	va_touchkit_link_dirs = { "addons/vaTouchkit/libs/dc1394-osx/lib" }
  va_touchkit_link_libs = { "dc1394" }
end	
	
if os.is("linux") then
	va_touchkit_include_dirs = { "addons/vaTouchkit/include", "addons/vaTouchkit/libs/dc1394-linux/include" }
	va_touchkit_link_dirs = { "addons/vaTouchkit/libs/dc1394-linux/lib" }		
  va_touchkit_link_libs = { "dc1394" }
end	
	
if os.is("windows") then
	va_touchkit_include_dirs = { "addons/vaTouchkit/include", "addons/vaTouchkit/libs/flyCapture-win32/include" }
	va_touchkit_link_dirs = { "addons/vaTouchkit/libs/flyCapture-win32/lib" }				
  va_touchkit_link_libs = { "FlyCapture2" }
end


project "vaTouchkit"
	kind "StaticLib"
	location "addons/vaTouchkit"
	files { "addons/vaTouchkit/include/vaTouchkit/*.h", "addons/vaTouchkit/src/*.cpp" }
	includedirs { va_include_dirs, va_opencv_include_dirs, va_touchkit_include_dirs }
	
  configuration "Debug"
    targetdir "addons/vaTouchkit/bin/debug"
 
  configuration "Release"
    targetdir "addons/vaTouchkit/bin/release"	


if _ACTION == "clean" then
  os.rmdir("addons/vaTouchkit/bin")
  os.rmdir("addons/vaTouchkit/obj")
	os.rmdir("addons/vaTouchkit/vaTouchkit.xcodeproj")
	os.rmdir("addons/vaTouchkit/vaTouchkit.vcproj")
end

-- ------ vaTouchkit end ------------------------------------------------------



-- ------ examples ------------------------------------------------------------
-- ----------------------------------------------------------------------------

project "exampleKeymouse"
	kind "WindowedApp"
	location "apps/examples/exampleKeymouse"
	files { "apps/examples/exampleKeymouse/src/*.h", "apps/examples/exampleKeymouse/src/*.cpp" }
	
	includedirs { va_include_dirs }
	libdirs { va_link_dirs }
	links { "va", va_link_libs }	
	
  configuration "Debug"
    targetdir "apps/examples/exampleKeymouse/bin/debug"
 
  configuration "Release"
    targetdir "apps/examples/exampleKeymouse/bin/release"


project "exampleShapes"
	kind "WindowedApp"
	location "apps/examples/exampleShapes"
	files { "apps/examples/exampleShapes/src/*.h", "apps/examples/exampleShapes/src/*.cpp" }
	
	includedirs { va_include_dirs }
	libdirs { va_link_dirs }
	links { "va", va_link_libs }	
	
  configuration "Debug"
    targetdir "apps/examples/exampleShapes/bin/debug"
 
  configuration "Release"
    targetdir "apps/examples/exampleShapes/bin/release"


project "exampleWidget"
	kind "WindowedApp"
	location "apps/examples/exampleWidget"
	files { "apps/examples/exampleWidget/src/*.h", "apps/examples/exampleWidget/src/*.cpp" }
	
	includedirs { va_include_dirs }
	libdirs { va_link_dirs }
	links { "va", va_link_libs }	
	
  configuration "Debug"
    targetdir "apps/examples/exampleWidget/bin/debug"
 
  configuration "Release"
    targetdir "apps/examples/exampleWidget/bin/release"


if _ACTION == "clean" then
  os.rmdir("apps/examples/exampleKeymouse/bin")
  os.rmdir("apps/examples/exampleKeymouse/obj")
	os.rmdir("apps/examples/exampleKeymouse/exampleKeymouse.xcodeproj")
	os.rmdir("apps/examples/exampleKeymouse/exampleKeymouse.vcproj")

  os.rmdir("apps/examples/exampleShapes/bin")
  os.rmdir("apps/examples/exampleShapes/obj")
	os.rmdir("apps/examples/exampleShapes/exampleShapes.xcodeproj")
	os.rmdir("apps/examples/exampleShapes/exampleShapes.vcproj")

  os.rmdir("apps/examples/exampleWidget/bin")
  os.rmdir("apps/examples/exampleWidget/obj")
	os.rmdir("apps/examples/exampleWidget/exampleWidget.xcodeproj")
	os.rmdir("apps/examples/exampleWidget/exampleWidget.vcproj")
end

-- ----------------------------------------------------------------------------
-- ------ examples end --------------------------------------------------------



-- ------ addons examples -----------------------------------------------------
-- ----------------------------------------------------------------------------

project "exampleGestureWidget"
	kind "WindowedApp"
	location "apps/addonExamples/exampleGestureWidget"
	files { "apps/addonExamples/exampleGestureWidget/src/*.h", "apps/addonExamples/exampleGestureWidget/src/*.cpp" }
	
	includedirs { va_include_dirs, va_multipad_include_dirs }
	libdirs { va_link_dirs, va_multipad_link_dirs }
	links { "va", va_link_libs, "vaMultipad", va_multipad_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleGestureWidget/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleGestureWidget/bin/release"


project "exampleMice"
	kind "WindowedApp"
	location "apps/addonExamples/exampleMice"
	files { "apps/addonExamples/exampleMice/src/*.h", "apps/addonExamples/exampleMice/src/*.cpp" }
	
	includedirs { va_include_dirs, va_mice_include_dirs }
	libdirs { va_link_dirs, va_mice_link_dirs }
	links { "va", va_link_libs, "vaMice", va_mice_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleMice/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleMice/bin/release"


project "exampleMultipad"
	kind "WindowedApp"
	location "apps/addonExamples/exampleMultipad"
	files { "apps/addonExamples/exampleMultipad/src/*.h", "apps/addonExamples/exampleMultipad/src/*.cpp" }
	
	includedirs { va_include_dirs, va_multipad_include_dirs }
	libdirs { va_link_dirs, va_multipad_link_dirs }
	links { "va", va_link_libs, "vaMultipad", va_multipad_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleMultipad/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleMultipad/bin/release"


project "exampleMultipadGamepad"
	kind "WindowedApp"
	location "apps/addonExamples/exampleMultipadGamepad"
	files { "apps/addonExamples/exampleMultipadGamepad/src/*.h", "apps/addonExamples/exampleMultipadGamepad/src/*.cpp" }
	
	includedirs { va_include_dirs, va_multipad_include_dirs }
	libdirs { va_link_dirs, va_multipad_link_dirs }
	links { "va", va_link_libs, "vaMultipad", va_multipad_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleMultipadGamepad/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleMultipadGamepad/bin/release"


project "exampleNetworkTcpClient"
	kind "WindowedApp"
	location "apps/addonExamples/exampleNetworkTcpClient"
	files { "apps/addonExamples/exampleNetworkTcpClient/src/*.h", "apps/addonExamples/exampleNetworkTcpClient/src/*.cpp" }
	
	includedirs { va_include_dirs, va_network_include_dirs }
	libdirs { va_link_dirs, va_network_link_dirs }
	links { "va", va_link_libs, "vaNetwork", va_network_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleNetworkTcpClient/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleNetworkTcpClient/bin/release"


project "exampleNetworkTcpServer"
	kind "WindowedApp"
	location "apps/addonExamples/exampleNetworkTcpServer"
	files { "apps/addonExamples/exampleNetworkTcpServer/src/*.h", "apps/addonExamples/exampleNetworkTcpServer/src/*.cpp" }
	
	includedirs { va_include_dirs, va_network_include_dirs }
	libdirs { va_link_dirs, va_network_link_dirs }
	links { "va", va_link_libs, "vaNetwork", va_network_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleNetworkTcpServer/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleNetworkTcpServer/bin/release"


project "exampleNetworkUdpReceiver"
	kind "WindowedApp"
	location "apps/addonExamples/exampleNetworkUdpReceiver"
	files { "apps/addonExamples/exampleNetworkUdpReceiver/src/*.h", "apps/addonExamples/exampleNetworkUdpReceiver/src/*.cpp" }
	
	includedirs { va_include_dirs, va_network_include_dirs }
	libdirs { va_link_dirs, va_network_link_dirs }
	links { "va", va_link_libs, "vaNetwork", va_network_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleNetworkUdpReceiver/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleNetworkUdpReceiver/bin/release"


project "exampleNetworkUdpSender"
	kind "WindowedApp"
	location "apps/addonExamples/exampleNetworkUdpSender"
	files { "apps/addonExamples/exampleNetworkUdpSender/src/*.h", "apps/addonExamples/exampleNetworkUdpSender/src/*.cpp" }
	
	includedirs { va_include_dirs, va_network_include_dirs }
	libdirs { va_link_dirs, va_network_link_dirs }
	links { "va", va_link_libs, "vaNetwork", va_network_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleNetworkUdpSender/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleNetworkUdpSender/bin/release"


project "exampleOpenal"
	kind "WindowedApp"
	location "apps/addonExamples/exampleOpenal"
	files { "apps/addonExamples/exampleOpenal/src/*.h", "apps/addonExamples/exampleOpenal/src/*.cpp" }
	
	includedirs { va_include_dirs, va_openal_include_dirs }
	libdirs { va_link_dirs, va_openal_link_dirs }
	links { "va", va_link_libs, "vaOpenal", va_openal_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleOpenal/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleOpenal/bin/release"


project "exampleOscReceiver"
	kind "WindowedApp"
	location "apps/addonExamples/exampleOscReceiver"
	files { "apps/addonExamples/exampleOscReceiver/src/*.h", "apps/addonExamples/exampleOscReceiver/src/*.cpp" }
	
	includedirs { va_include_dirs, va_osc_include_dirs }
	libdirs { va_link_dirs, va_osc_link_dirs }
	links { "va", va_link_libs, "vaOsc", va_osc_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleOscReceiver/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleOscReceiver/bin/release"


project "exampleOscSender"
	kind "WindowedApp"
	location "apps/addonExamples/exampleOscSender"
	files { "apps/addonExamples/exampleOscSender/src/*.h", "apps/addonExamples/exampleOscSender/src/*.cpp" }
	
	includedirs { va_include_dirs, va_osc_include_dirs }
	libdirs { va_link_dirs, va_osc_link_dirs }
	links { "va", va_link_libs, "vaOsc", va_osc_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleOscSender/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleOscSender/bin/release"


project "exampleSoundInstrument"
	kind "WindowedApp"
	location "apps/addonExamples/exampleSoundInstrument"
	files { "apps/addonExamples/exampleSoundInstrument/src/*.h", "apps/addonExamples/exampleSoundInstrument/src/*.cpp" }
	
	includedirs { va_include_dirs, va_sound_include_dirs }
	libdirs { va_link_dirs, va_sound_link_dirs }
	links { "va", va_link_libs, "vaSound", va_sound_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleSoundInstrument/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleSoundInstrument/bin/release"

  configuration { "macosx" }
		defines { "__MACOSX_CORE__", "__LITTLE_ENDIAN__" }

  configuration { "linux" }
		defines { "__LINUX_ALSA__", "__LINUX_ALSASEQ__", "__LITTLE_ENDIAN__" }
		
  configuration { "windows" }
		defines { "__WINDOWS_DS__", "__WINDOWS_MM__", "__LITTLE_ENDIAN__" }
		

project "exampleSoundSine"
	kind "WindowedApp"
	location "apps/addonExamples/exampleSoundSine"
	files { "apps/addonExamples/exampleSoundSine/src/*.h", "apps/addonExamples/exampleSoundSine/src/*.cpp" }
	
	includedirs { va_include_dirs, va_sound_include_dirs }
	libdirs { va_link_dirs, va_sound_link_dirs }
	links { "va", va_link_libs, "vaSound", va_sound_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleSoundSine/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleSoundSine/bin/release"

  configuration { "macosx" }
		defines { "__MACOSX_CORE__", "__LITTLE_ENDIAN__" }

  configuration { "linux" }
		defines { "__LINUX_ALSA__", "__LINUX_ALSASEQ__", "__LITTLE_ENDIAN__" }
		
  configuration { "windows" }
		defines { "__WINDOWS_DS__", "__WINDOWS_MM__", "__LITTLE_ENDIAN__" }
		

project "exampleTouchkitSimple"
	kind "WindowedApp"
	location "apps/addonExamples/exampleTouchkitSimple"
	files { "apps/addonExamples/exampleTouchkitSimple/src/*.h", "apps/addonExamples/exampleTouchkitSimple/src/*.cpp" }
	
	includedirs { va_include_dirs, va_opencv_include_dirs, va_touchkit_include_dirs }
	libdirs { va_link_dirs, va_opencv_link_dirs, va_touchkit_link_dirs }
	links { "va", va_link_libs, "vaOpencv", va_opencv_link_libs, "vaTouchkit", va_touchkit_link_libs }	
	
  configuration "Debug"
    targetdir "apps/addonExamples/exampleTouchkitSimple/bin/debug"
 
  configuration "Release"
    targetdir "apps/addonExamples/exampleTouchkitSimple/bin/release"
		

if _ACTION == "clean" then
  os.rmdir("apps/addonExamples/exampleGestureWidget/bin")
  os.rmdir("apps/addonExamples/exampleGestureWidget/obj")
	os.rmdir("apps/addonExamples/exampleGestureWidget/exampleGestureWidget.xcodeproj")
	os.rmdir("apps/addonExamples/exampleGestureWidget/exampleGestureWidget.vcproj")

  os.rmdir("apps/addonExamples/exampleMice/bin")
  os.rmdir("apps/addonExamples/exampleMice/obj")
	os.rmdir("apps/addonExamples/exampleMice/exampleMice.xcodeproj")
	os.rmdir("apps/addonExamples/exampleMice/exampleMice.vcproj")
	
  os.rmdir("apps/addonExamples/exampleMultipad/bin")
  os.rmdir("apps/addonExamples/exampleMultipad/obj")
	os.rmdir("apps/addonExamples/exampleMultipad/exampleMultipad.xcodeproj")
	os.rmdir("apps/addonExamples/exampleMultipad/exampleMultipad.vcproj")
	
  os.rmdir("apps/addonExamples/exampleMultipadGamepad/bin")
  os.rmdir("apps/addonExamples/exampleMultipadGamepad/obj")
	os.rmdir("apps/addonExamples/exampleMultipadGamepad/exampleMultipadGamepad.xcodeproj")
	os.rmdir("apps/addonExamples/exampleMultipadGamepad/exampleMultipadGamepad.vcproj")

  os.rmdir("apps/addonExamples/exampleNetworkTcpClient/bin")
  os.rmdir("apps/addonExamples/exampleNetworkTcpClient/obj")
	os.rmdir("apps/addonExamples/exampleNetworkTcpClient/exampleNetworkTcpClient.xcodeproj")
	os.rmdir("apps/addonExamples/exampleNetworkTcpClient/exampleNetworkTcpClient.vcproj")
			
  os.rmdir("apps/addonExamples/exampleNetworkTcpServer/bin")
  os.rmdir("apps/addonExamples/exampleNetworkTcpServer/obj")
	os.rmdir("apps/addonExamples/exampleNetworkTcpServer/exampleNetworkTcpServer.xcodeproj")
	os.rmdir("apps/addonExamples/exampleNetworkTcpServer/exampleNetworkTcpServer.vcproj")
			
  os.rmdir("apps/addonExamples/exampleNetworkUdpReceiver/bin")
  os.rmdir("apps/addonExamples/exampleNetworkUdpReceiver/obj")
	os.rmdir("apps/addonExamples/exampleNetworkUdpReceiver/exampleNetworkUdpReceiver.xcodeproj")
	os.rmdir("apps/addonExamples/exampleNetworkUdpReceiver/exampleNetworkUdpReceiver.vcproj")
			
  os.rmdir("apps/addonExamples/exampleNetworkUdpSender/bin")
  os.rmdir("apps/addonExamples/exampleNetworkUdpSender/obj")
	os.rmdir("apps/addonExamples/exampleNetworkUdpSender/exampleNetworkUdpSender.xcodeproj")
	os.rmdir("apps/addonExamples/exampleNetworkUdpSender/exampleNetworkUdpSender.vcproj")
			
  os.rmdir("apps/addonExamples/exampleOpenal/bin")
  os.rmdir("apps/addonExamples/exampleOpenal/obj")
	os.rmdir("apps/addonExamples/exampleOpenal/exampleOpenal.xcodeproj")
	os.rmdir("apps/addonExamples/exampleOpenal/exampleOpenal.vcproj")

  os.rmdir("apps/addonExamples/exampleOscReceiver/bin")
  os.rmdir("apps/addonExamples/exampleOscReceiver/obj")
	os.rmdir("apps/addonExamples/exampleOscReceiver/exampleOscReceiver.xcodeproj")
	os.rmdir("apps/addonExamples/exampleOscReceiver/exampleOscReceiver.vcproj")
	
  os.rmdir("apps/addonExamples/exampleOscSender/bin")
  os.rmdir("apps/addonExamples/exampleOscSender/obj")
	os.rmdir("apps/addonExamples/exampleOscSender/exampleOscSender.xcodeproj")
	os.rmdir("apps/addonExamples/exampleOscSender/exampleOscSender.vcproj")	

  os.rmdir("apps/addonExamples/exampleSoundInstrument/bin")
  os.rmdir("apps/addonExamples/exampleSoundInstrument/obj")
	os.rmdir("apps/addonExamples/exampleSoundInstrument/exampleSoundInstrument.xcodeproj")
	os.rmdir("apps/addonExamples/exampleSoundInstrument/exampleSoundInstrument.vcproj")	

  os.rmdir("apps/addonExamples/exampleSoundSine/bin")
  os.rmdir("apps/addonExamples/exampleSoundSine/obj")
	os.rmdir("apps/addonExamples/exampleSoundSine/exampleSoundSine.xcodeproj")
	os.rmdir("apps/addonExamples/exampleSoundSine/exampleSoundSine.vcproj")	

  os.rmdir("apps/addonExamples/exampleTouchkitSimple/bin")
  os.rmdir("apps/addonExamples/exampleTouchkitSimple/obj")
	os.rmdir("apps/addonExamples/exampleTouchkitSimple/exampleTouchkitSimple.xcodeproj")
	os.rmdir("apps/addonExamples/exampleTouchkitSimple/exampleTouchkitSimple.vcproj")
end

-- ----------------------------------------------------------------------------
-- ------ addons examples end -------------------------------------------------



-- ------ myApps --------------------------------------------------------------
-- ----------------------------------------------------------------------------

project "gridderTest"
	kind "WindowedApp"
	location "apps/myApps/gridderTest"
	files { "apps/myApps/gridderTest/src/*.h", "apps/myApps/gridderTest/src/*.cpp" }
	
	includedirs { va_include_dirs, va_opencv_include_dirs, va_touchkit_include_dirs }
	libdirs { va_link_dirs, va_opencv_link_dirs, va_touchkit_link_dirs }
	links { "va", va_link_libs, "vaOpencv", va_opencv_link_libs, "vaTouchkit", va_touchkit_link_libs }	
	
  configuration "Debug"
    targetdir "apps/myApps/gridderTest/bin/debug"
 
  configuration "Release"
    targetdir "apps/myApps/gridderTest/bin/release"


project "lasersaurSimulator"
	kind "WindowedApp"
	location "apps/myApps/lasersaurSimulator"
	files { "apps/myApps/lasersaurSimulator/src/*.h", "apps/myApps/lasersaurSimulator/src/*.cpp" }
	
	includedirs { va_include_dirs, va_network_include_dirs }
	libdirs { va_link_dirs, va_network_link_dirs }
	links { "va", va_link_libs, "vaNetwork", va_network_link_libs }	
	
  configuration "Debug"
    targetdir "apps/myApps/lasersaurSimulator/bin/debug"
 
  configuration "Release"
    targetdir "apps/myApps/lasersaurSimulator/bin/release"


project "storm"
	kind "WindowedApp"
	location "apps/myApps/storm"
	files { "apps/myApps/storm/src/*.h", "apps/myApps/storm/src/*.cpp" }
	
	includedirs { va_include_dirs, va_opencv_include_dirs, va_touchkit_include_dirs }
	libdirs { va_link_dirs, va_opencv_link_dirs, va_touchkit_link_dirs }
	links { "va", va_link_libs, "vaOpencv", va_opencv_link_libs, "vaTouchkit", va_touchkit_link_libs }	
	
  configuration "Debug"
    targetdir "apps/myApps/storm/bin/debug"
 
  configuration "Release"
    targetdir "apps/myApps/storm/bin/release"


project "osgmovie"
	kind "WindowedApp"
	location "apps/osgExamples/osgmovie"
	files { "apps/osgExamples/osgmovie/src/*.h", "apps/osgExamples/osgmovie/src/*.cpp" }
	
	includedirs { va_include_dirs }	
	libdirs { va_link_dirs }
	links { va_link_libs }	
	
  configuration "Debug"
    targetdir "apps/osgExamples/osgmovie/bin/debug"
 
  configuration "Release"
    targetdir "apps/osgExamples/osgmovie/bin/release"


if _ACTION == "clean" then
  os.rmdir("apps/myApps/gridderTest/bin")
  os.rmdir("apps/myApps/gridderTest/obj")
	os.rmdir("apps/myApps/gridderTest/gridderTest.xcodeproj")
	os.rmdir("apps/myApps/gridderTest/gridderTest.vcproj")

  os.rmdir("apps/myApps/lasersaurSimulator/bin")
  os.rmdir("apps/myApps/lasersaurSimulator/obj")
	os.rmdir("apps/myApps/lasersaurSimulator/lasersaurSimulator.xcodeproj")
	os.rmdir("apps/myApps/lasersaurSimulator/lasersaurSimulator.vcproj")
	
  os.rmdir("apps/myApps/storm/bin")
  os.rmdir("apps/myApps/storm/obj")
	os.rmdir("apps/myApps/storm/storm.xcodeproj")
	os.rmdir("apps/myApps/storm/storm.vcproj")

  os.rmdir("apps/osgExamples/osgmovie/bin")
  os.rmdir("apps/osgExamples/osgmovie/obj")
	os.rmdir("apps/osgExamples/osgmovie/osgmovie.xcodeproj")
	os.rmdir("apps/osgExamples/osgmovie/osgmovie.vcproj")	
end

-- ----------------------------------------------------------------------------
-- ------ myApps end ----------------------------------------------------------

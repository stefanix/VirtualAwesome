
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
		defines "WIN32"


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



include "apps/examples/exampleKeymouse"
include "apps/examples/exampleShapes"
include "apps/examples/exampleWidget"


-- ------ addons examples -----------------------------------------------------
-- ----------------------------------------------------------------------------

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
  os.rmdir("apps/addonExamples/exampleOpenal/bin")
  os.rmdir("apps/addonExamples/exampleOpenal/obj")
	os.rmdir("apps/addonExamples/exampleOpenal/exampleOpenal.xcodeproj")
	os.rmdir("apps/addonExamples/exampleOpenal/exampleOpenal.vcproj")

  os.rmdir("apps/addonExamples/exampleTouchkitSimple/bin")
  os.rmdir("apps/addonExamples/exampleTouchkitSimple/obj")
	os.rmdir("apps/addonExamples/exampleTouchkitSimple/exampleTouchkitSimple.xcodeproj")
	os.rmdir("apps/addonExamples/exampleTouchkitSimple/exampleTouchkitSimple.vcproj")
end

-- ----------------------------------------------------------------------------
-- ------ addons examples end -------------------------------------------------

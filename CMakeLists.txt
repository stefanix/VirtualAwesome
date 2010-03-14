CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

PROJECT( virtualAwesome )

# SET( CMAKE_CONFIGURATION_TYPES "Release" CACHE INTERNAL "Build Type" FORCE )
# SET( CMAKE_BUILD_TYPE Debug CACHE STRING "Options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )

# hide a few options from "simple view" in the gui
MARK_AS_ADVANCED( CMAKE_CONFIGURATION_TYPES )
MARK_AS_ADVANCED( CMAKE_BUILD_TYPE )
MARK_AS_ADVANCED( CMAKE_OSX_ARCHITECTURES )
MARK_AS_ADVANCED( CMAKE_INSTALL_PREFIX )
MARK_AS_ADVANCED( CMAKE_OSX_SYSROOT )


ADD_DEFINITIONS(-DOSG_LIBRARY_STATIC)
# ADD_DEFINITIONS(-pedantic -fvisibility=hidden)
IF(UNIX)
	ADD_DEFINITIONS(-Wall -Wparentheses -Wno-long-long -Wno-import -pedantic -Wreturn-type -Wmissing-braces -Wunknown-pragmas -Wunused)
ENDIF()


SET( VA_HEADER_DIRECTORY  ${PROJECT_SOURCE_DIR}/libs/va/include )
SET( VA_SOURCE_DIRECTORY  ${PROJECT_SOURCE_DIR}/libs/va/src )
SET( VA_BINARY_DIRECTORY  ${PROJECT_SOURCE_DIR}/libs/va/bin )


# include directory for VirtualAwesome
INCLUDE_DIRECTORIES( ${VA_HEADER_DIRECTORY} )


# ------------ Platform specifics
IF(UNIX)
IF(APPLE)
	# OSX
	
	# Set SDK
	#
	SET( CMAKE_OSX_SYSROOT  "/Developer/SDKs/MacOSX10.5.sdk" )
	SET( CMAKE_OSX_DEPLOYMENT_TARGET  "10.5" )
	MARK_AS_ADVANCED( CMAKE_OSX_DEPLOYMENT_TARGET )
	SET( CMAKE_OSX_ARCHITECTURES  "i386" )
	# match visibility of osg, a warning issue
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.5 -ftree-vectorize -fvisibility-inlines-hidden" CACHE STRING "Flags used by the compiler during all build types." FORCE)

	
	# Find osx frameworks
	#
	INCLUDE_DIRECTORIES( /Developer/Headers/FlatCarbon )
	FIND_LIBRARY(AGL_LIBRARY AGL)
	FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
	FIND_LIBRARY(ATBOX_LIBRARY AudioToolbox)
	FIND_LIBRARY(CARBON_LIBRARY Carbon)
	FIND_LIBRARY(CAUDIO_LIBRARY CoreAudio)
	FIND_LIBRARY(CFOUNDATION_LIBRARY CoreFoundation)
	FIND_LIBRARY(CSERVICES_LIBRARY CoreServices)
	FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
	FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime )
	FIND_LIBRARY(IOKIT_LIBRARY IOKit )
	
	MARK_AS_ADVANCED (AGL_LIBRARY
			 APP_SERVICES_LIBRARY
			 ATBOX_LIBRARY
			 CARBON_LIBRARY
			 CAUDIO_LIBRARY
			 CFOUNDATION_LIBRARY
			 CSERVICES_LIBRARY
			 OPENGL_LIBRARY
			 QUICKTIME_LIBRARY
			 IOKIT_LIBRARY)
	SET(OSX_FRAMEWORKS ${AGL_LIBRARY} 
	                   ${APP_SERVICES_LIBRARY} 
	                   ${ATBOX_LIBRARY} 
	                   ${CARBON_LIBRARY} 
	                   ${CAUDIO_LIBRARY} 
	                   ${CFOUNDATION_LIBRARY} 
	                   ${CSERVICES_LIBRARY} 
	                   ${OPENGL_LIBRARY} 
	                   ${QUICKTIME_LIBRARY}
					   ${IOKIT_LIBRARY})
	
	
	# set the executable to build
	#
	SET(EXECUTABLE_TYPE MACOSX_BUNDLE)
	
	# include directory for OSG
	INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/osg-osx/include )
		
	# set common target libs for apps
	#
	SET( VA_LINK_LIBRARIES
		${OSX_FRAMEWORKS}
		${PROJECT_SOURCE_DIR}/libs/freetype-osx/lib/freetype.a	
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgViewer.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_freetype.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_qt.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_bmp.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_osg.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_obj.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_3ds.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_dxf.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgdb_stl.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgGA.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgText.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgDB.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosgUtil.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libosg.a 
		${PROJECT_SOURCE_DIR}/libs/osg-osx/lib/libOpenThreads.a		
	)




ELSE()
	# Linux
	
	FIND_PACKAGE(X11)
	FIND_PACKAGE(OpenGL)
	# FIND_PACKAGE(FreeType)
	FIND_PACKAGE(ZLIB)
    # FIND_PACKAGE(GIFLIB)
    FIND_PACKAGE(JPEG)
    FIND_PACKAGE(PNG)
    # FIND_PACKAGE(TIFF)
	SET( LINUX_TARGET_LIBRARIES  
		${X11_LIBRARY}
		${OpenGL_LIBRARY}
		${ZLIB_LIBRARY}
		${JPEG_LIBRARY}
		${PNG_LIBRARY}
	)
	
	# include directory for OSG
	INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/osg-linux/include )
		
	# set common target libs for apps
	#
	SET( VA_LINK_LIBRARIES
		pthread m GL GLU SM ICE X11 Xext Xrandr z freetype jpeg png
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgViewer.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_freetype.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_png.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_jpeg.a
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_bmp.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_osg.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_obj.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_3ds.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_dxf.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgdb_stl.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgGA.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgText.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgDB.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosgUtil.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libosg.a 
		${PROJECT_SOURCE_DIR}/libs/osg-linux/lib/libOpenThreads.a	
	)
ENDIF(APPLE)
ENDIF(UNIX)



IF(WIN32)
	# Windows

	# FIND_PACKAGE(OpenGL)
	# FIND_PACKAGE(FreeType)
    # FIND_PACKAGE(JPEG)
    # FIND_PACKAGE(PNG)
	# FIND_PACKAGE(ZLIB)	
	# FIND_PACKAGE(QuickTime)
	
	# include directory for OSG
	INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/osg-win32/include )	
	
	# set common target libs for apps
	#
	SET( VA_LINK_LIBRARIES
		OpenGL32.lib GLu32.lib kernel32.lib setupapi.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib
		
		optimized  ${PROJECT_SOURCE_DIR}/libs/freetype-win32/lib/freetype2311.lib	
		optimized  ${PROJECT_SOURCE_DIR}/libs/jpeg-win32/lib/jpeg.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/png-win32/lib/libpng12_static.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/zlib-win32/lib/zlib.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgViewer.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_freetype.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_png.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_jpeg.lib
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_bmp.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_osg.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_obj.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_3ds.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_dxf.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_stl.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgGA.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgText.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgDB.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgUtil.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osg.lib 
		optimized  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/ot11-OpenThreads.lib
			
		debug  ${PROJECT_SOURCE_DIR}/libs/freetype-win32/lib/freetype2311_D.lib	
		debug  ${PROJECT_SOURCE_DIR}/libs/jpeg-win32/lib/jpegD.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/png-win32/lib/libpng12_staticd.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/zlib-win32/lib/zlibD.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgViewerd.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_freetyped.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_pngd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_jpegd.lib
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_bmpd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_osgd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_objd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_3dsd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_dxfd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osgdb_stld.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgGAd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgTextd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgDBd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgUtild.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/osg55-osgd.lib 
		debug  ${PROJECT_SOURCE_DIR}/libs/osg-win32/lib/ot11-OpenThreadsd.lib	
	)	
	
	SET( ZLIB_DLL_RUNTIME  ${PROJECT_SOURCE_DIR}/libs/zlib-win32/bin/zlib1.dll )
	SET( PNG_DLL_RUNTIME  ${PROJECT_SOURCE_DIR}/libs/png-win32/bin/libpng13.dll )	
ENDIF()
# ------------ end platform specifics



MACRO( POST_BUILD_COPY_FILE  source_file  target_path )
	ADD_CUSTOM_COMMAND( 
		TARGET ${EXAMPLE_NAME}
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E make_directory
	    "${target_path}"
	)
	ADD_CUSTOM_COMMAND( 
		TARGET ${EXAMPLE_NAME}
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${source_file}"
	    "${target_path}"
	)
ENDMACRO()



###########################################
# LIBS
###########################################

# ----------------------------------------< virtualAwesome >
ADD_LIBRARY( va STATIC
    ${VA_HEADER_DIRECTORY}/va/App.h
    ${VA_HEADER_DIRECTORY}/va/BoxShape.h
    ${VA_HEADER_DIRECTORY}/va/ButtonWidget.h
    ${VA_HEADER_DIRECTORY}/va/Constants.h
    ${VA_HEADER_DIRECTORY}/va/CircleShape.h
    ${VA_HEADER_DIRECTORY}/va/EllipseShape.h
    ${VA_HEADER_DIRECTORY}/va/EventHandlers.h
    ${VA_HEADER_DIRECTORY}/va/GuiEvents.h
    ${VA_HEADER_DIRECTORY}/va/ImageShape.h
    ${VA_HEADER_DIRECTORY}/va/Key.h
    ${VA_HEADER_DIRECTORY}/va/LineShape.h
    ${VA_HEADER_DIRECTORY}/va/Main.h
    ${VA_HEADER_DIRECTORY}/va/Model.h
    ${VA_HEADER_DIRECTORY}/va/MonsterShape.h
    ${VA_HEADER_DIRECTORY}/va/Mouse.h
    ${VA_HEADER_DIRECTORY}/va/Node.h
    ${VA_HEADER_DIRECTORY}/va/PanelWidget.h
    ${VA_HEADER_DIRECTORY}/va/Pen.h
    ${VA_HEADER_DIRECTORY}/va/RectangleShape.h
    ${VA_HEADER_DIRECTORY}/va/Scene.h
    ${VA_HEADER_DIRECTORY}/va/Shape.h
    ${VA_HEADER_DIRECTORY}/va/SliderWidget.h
    ${VA_HEADER_DIRECTORY}/va/TextShape.h
    ${VA_HEADER_DIRECTORY}/va/TextureGeometry.h
    ${VA_HEADER_DIRECTORY}/va/ToggleWidget.h
    ${VA_HEADER_DIRECTORY}/va/Touch.h
    ${VA_HEADER_DIRECTORY}/va/TouchShape.h    
    ${VA_HEADER_DIRECTORY}/va/TriangleShape.h
    ${VA_HEADER_DIRECTORY}/va/Types.h
    ${VA_HEADER_DIRECTORY}/va/VertexGeometry.h
    ${VA_HEADER_DIRECTORY}/va/VertexShape.h
    ${VA_HEADER_DIRECTORY}/va/Visitors.h
    ${VA_HEADER_DIRECTORY}/va/Widget.h

    ${VA_SOURCE_DIRECTORY}/App.cpp
    ${VA_SOURCE_DIRECTORY}/ButtonWidget.cpp
    ${VA_SOURCE_DIRECTORY}/CircleShape.cpp
    ${VA_SOURCE_DIRECTORY}/EllipseShape.cpp
    ${VA_SOURCE_DIRECTORY}/GuiEvents.cpp
    ${VA_SOURCE_DIRECTORY}/ImageShape.cpp
    ${VA_SOURCE_DIRECTORY}/LineShape.cpp
    ${VA_SOURCE_DIRECTORY}/Model.cpp
    ${VA_SOURCE_DIRECTORY}/MonsterShape.cpp
    ${VA_SOURCE_DIRECTORY}/Node.cpp
    ${VA_SOURCE_DIRECTORY}/PanelWidget.cpp
    ${VA_SOURCE_DIRECTORY}/RectangleShape.cpp
    ${VA_SOURCE_DIRECTORY}/Scene.cpp
    ${VA_SOURCE_DIRECTORY}/SliderWidget.cpp
    ${VA_SOURCE_DIRECTORY}/TextShape.cpp
    ${VA_SOURCE_DIRECTORY}/TextureGeometry.cpp
    ${VA_SOURCE_DIRECTORY}/ToggleWidget.cpp
    ${VA_SOURCE_DIRECTORY}/TouchShape.cpp    
    ${VA_SOURCE_DIRECTORY}/TriangleShape.cpp
    ${VA_SOURCE_DIRECTORY}/VertexGeometry.cpp
    ${VA_SOURCE_DIRECTORY}/VertexShape.cpp
    ${VA_SOURCE_DIRECTORY}/Visitors.cpp
    ${VA_SOURCE_DIRECTORY}/Widget.cpp

)


SET_TARGET_PROPERTIES( va PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_BINARY_DIRECTORY}
)
# ----------------------------------------</ virtualAwesome >



###########################################
# ADDONS
###########################################

OPTION( BUILD_ADDON_VA_TOUCHKIT "Build the vaTouchkit addon." ON)
IF( BUILD_ADDON_VA_TOUCHKIT )
	ADD_SUBDIRECTORY( addons/vaOpencv )
	ADD_SUBDIRECTORY( addons/vaTouchkit )
ENDIF()

IF(APPLE)
	OPTION( BUILD_ADDON_VA_MULTIPAD "Build the vaMultipad addon. Needs a Snow Leopard MacBook" OFF)
	IF( BUILD_ADDON_VA_MULTIPAD )
		ADD_SUBDIRECTORY( addons/vaMultipad )
	ENDIF()
ENDIF()

OPTION( BUILD_ADDON_VA_MICE "Build the vaMice addon." ON)
IF( BUILD_ADDON_VA_MICE )
	ADD_SUBDIRECTORY( addons/vaMice )
ENDIF()

OPTION( BUILD_ADDON_VA_TWEEN "Build the vaTween addon." ON)
IF( BUILD_ADDON_VA_TWEEN )
	ADD_SUBDIRECTORY( addons/vaTween )
ENDIF()

OPTION( BUILD_ADDON_VA_SOUND "Build the vaSound addon." ON)
IF( BUILD_ADDON_VA_SOUND )
	ADD_SUBDIRECTORY( addons/vaSound )
ENDIF()


###########################################
# EXAMPLES
###########################################

OPTION( BUILD_EXAMPLES "Build the stock examples." ON)
IF( BUILD_EXAMPLES )
	IF( BUILD_ADDON_VA_TOUCHKIT )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleTouchkitSimple )
	ENDIF()

	IF( BUILD_ADDON_VA_MULTIPAD )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleMultipad )
	ENDIF()

	IF( BUILD_ADDON_VA_MICE )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleMice )
	ENDIF()

	IF( BUILD_ADDON_VA_SOUND )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleSoundSine )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleSoundInstrument )
	ENDIF()

	IF( BUILD_ADDON_VA_TWEEN )
		ADD_SUBDIRECTORY( apps/addonExamples/exampleTween )
	ENDIF()
		
	ADD_SUBDIRECTORY( apps/examples/exampleKeymouse )
	ADD_SUBDIRECTORY( apps/examples/exampleShapes )
	ADD_SUBDIRECTORY( apps/examples/exampleWidget )
ENDIF()



###########################################
# APPS
###########################################

ADD_SUBDIRECTORY( apps/snowDrift/storm )



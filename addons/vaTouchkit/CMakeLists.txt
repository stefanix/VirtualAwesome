

SET( VA_TOUCHKIT_ROOT ${PROJECT_SOURCE_DIR}/addons/vaTouchkit )


INCLUDE_DIRECTORIES( ${VA_OPENCV_INCLUDES} )

	
ADD_LIBRARY( vaTouchkit STATIC
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/AdaptiveFilter.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/Blob.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/BlobTracker.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/Contour.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/ContourFinder.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/JpegGrabber.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/Tracker.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/VideoGrabber.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/VideoGrabberDc1394.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/VideoGrabberFlyCapture.h
	${VA_TOUCHKIT_ROOT}/include/vaTouchkit/VisionMap.h

	${VA_TOUCHKIT_ROOT}/src/AdaptiveFilter.cpp
	${VA_TOUCHKIT_ROOT}/src/Blob.cpp
	${VA_TOUCHKIT_ROOT}/src/BlobTracker.cpp
	${VA_TOUCHKIT_ROOT}/src/Contour.cpp
	${VA_TOUCHKIT_ROOT}/src/ContourFinder.cpp
	${VA_TOUCHKIT_ROOT}/src/JpegGrabber.cpp
	${VA_TOUCHKIT_ROOT}/src/Tracker.cpp
	${VA_TOUCHKIT_ROOT}/src/VideoGrabberDc1394.cpp
	${VA_TOUCHKIT_ROOT}/src/VideoGrabberFlyCapture.cpp	
	${VA_TOUCHKIT_ROOT}/src/VisionMap.cpp	
)


# -----< Platform specifics >
IF(UNIX)
IF(APPLE)
	# OSX

	# include directories for vaTouchkit
	SET( VA_TOUCHKIT_INCLUDES
		${VA_TOUCHKIT_ROOT}/include 
		${VA_TOUCHKIT_ROOT}/libs/dc1394-osx/include
	)
	SET( VA_TOUCHKIT_INCLUDES  ${VA_TOUCHKIT_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_TOUCHKIT_INCLUDES} )
		
	# set target link libs for addon
	SET( VA_TOUCHKIT_LINK_LIBRARIES
		${VA_TOUCHKIT_ROOT}/libs/dc1394-osx/lib/libdc1394.a			
	)
	SET( VA_TOUCHKIT_LINK_LIBRARIES  ${VA_TOUCHKIT_LINK_LIBRARIES}  PARENT_SCOPE )	
	
	
ELSE()
	# Linux

	# include directories for vaTouchkit
	SET( VA_TOUCHKIT_INCLUDES
		${VA_TOUCHKIT_ROOT}/include 
		${VA_TOUCHKIT_ROOT}/libs/dc1394-linux/include
	)
	SET( VA_TOUCHKIT_INCLUDES  ${VA_TOUCHKIT_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_TOUCHKIT_INCLUDES} )	
		
	# set target link libs for addon
	SET( VA_TOUCHKIT_LINK_LIBRARIES
		raw1394
		${VA_TOUCHKIT_ROOT}/libs/dc1394-linux/lib/libdc1394.a	
	)
	SET( VA_TOUCHKIT_LINK_LIBRARIES  ${VA_TOUCHKIT_LINK_LIBRARIES}  PARENT_SCOPE )		
	
ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
	# Windows

	# include directories for vaTouchkit
	SET( VA_TOUCHKIT_INCLUDES
		${VA_TOUCHKIT_ROOT}/include 
		${VA_TOUCHKIT_ROOT}/libs/flyCapture-win32/include
	)
	SET( VA_TOUCHKIT_INCLUDES  ${VA_TOUCHKIT_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_TOUCHKIT_INCLUDES} )		
		
	# set target link libs for addon
	SET( VA_TOUCHKIT_LINK_LIBRARIES
		${VA_TOUCHKIT_ROOT}/libs/flyCapture-win32/lib/FlyCapture2.lib		
	)
	SET( VA_TOUCHKIT_LINK_LIBRARIES  ${VA_TOUCHKIT_LINK_LIBRARIES}  PARENT_SCOPE )		
	
	SET( FLYCAPTURE_DLL_RUNTIME  ${VA_TOUCHKIT_ROOT}/libs/flyCapture-win32/bin/FlyCapture2.dll  PARENT_SCOPE )
	
ENDIF()
# -----</ Platform specifics>


TARGET_LINK_LIBRARIES( vaTouchkit  
	va  ${VA_LINK_LIBRARIES}
	vaTouchkit  ${VA_TOUCHKIT_LINK_LIBRARIES}
	vaOpencv ${VA_OPENCV_LINK_LIBRARIES}
)

SET_TARGET_PROPERTIES( vaTouchkit PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_TOUCHKIT_ROOT}/bin
)




SET( VA_OPENCV_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaOpencv )

	
ADD_LIBRARY( vaOpencv STATIC
	${VA_OPENCV_ROOT}/include/vaOpencv/Image.h
	${VA_OPENCV_ROOT}/src/Image.cpp	
)

# -----< Platform specifics >
IF(UNIX)
IF(APPLE)
	# OSX

	# include directory for opencv
	SET( VA_OPENCV_INCLUDES
		${VA_OPENCV_ROOT}/include 
		${VA_OPENCV_ROOT}/libs/opencv-osx/include
	)
	SET( VA_OPENCV_INCLUDES  ${VA_OPENCV_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENCV_INCLUDES} )
		
	# set target link libs for addon
	SET( VA_OPENCV_LINK_LIBRARIES  
		${VA_OPENCV_ROOT}/libs/opencv-osx/lib/libOpenCV.a
	)					
	SET( VA_OPENCV_LINK_LIBRARIES  ${VA_OPENCV_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ELSE()
	# Linux

	# include directory for opencv
	SET( VA_OPENCV_INCLUDES
		${VA_OPENCV_ROOT}/include 
		${VA_OPENCV_ROOT}/libs/opencv-linux/include
	)
	SET( VA_OPENCV_INCLUDES  ${VA_OPENCV_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENCV_INCLUDES} )	
	
		
	# set target link libs for addon
	SET( VA_OPENCV_LINK_LIBRARIES
		${VA_OPENCV_ROOT}/libs/opencv-linux/lib/libcv.a		
		${VA_OPENCV_ROOT}/libs/opencv-linux/lib/libcvaux.a	
		${VA_OPENCV_ROOT}/libs/opencv-linux/lib/libcxcore.a	
	)
	SET( VA_OPENCV_LINK_LIBRARIES  ${VA_OPENCV_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
	# Windows

	# include directory for opencv
	SET( VA_OPENCV_INCLUDES
		${VA_OPENCV_ROOT}/include 
		${VA_OPENCV_ROOT}/libs/opencv-win32/include
	)
	SET( VA_OPENCV_INCLUDES  ${VA_OPENCV_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENCV_INCLUDES} )	
		
	# set target link libs for addon
	SET( VA_OPENCV_LINK_LIBRARIES
		optimized  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cv110.lib	
		optimized  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cvaux110.lib	
		optimized  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cxcore110.lib	
		debug  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cv110d.lib	
		debug  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cvaux110d.lib	
		debug  ${VA_OPENCV_ROOT}/libs/opencv-win32/lib/cxcore110d.lib	
	)
	SET( VA_OPENCV_LINK_LIBRARIES  ${VA_OPENCV_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF()
# -----</ Platform specifics>


TARGET_LINK_LIBRARIES( vaOpencv  
	va  ${VA_LINK_LIBRARIES}
	vaOpencv  ${VA_OPENCV_LINK_LIBRARIES}
)

SET_TARGET_PROPERTIES( vaOpencv PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_OPENCV_ROOT}/bin
)




SET( VA_OPENAL_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaOpenal )


	
ADD_LIBRARY( vaOpenal STATIC
	${VA_OPENAL_ROOT}/include/vaOpenal/AudioDevice.h
	${VA_OPENAL_ROOT}/include/vaOpenal/AudioResource.h
	${VA_OPENAL_ROOT}/include/vaOpenal/Listener.h
	${VA_OPENAL_ROOT}/include/vaOpenal/Music.h
	${VA_OPENAL_ROOT}/include/vaOpenal/OpenAL.h
	${VA_OPENAL_ROOT}/include/vaOpenal/Resource.h
	${VA_OPENAL_ROOT}/include/vaOpenal/Sound.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundBuffer.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundFile.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundFileDefault.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundFileOgg.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundPlayer.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundStereo.h
	${VA_OPENAL_ROOT}/include/vaOpenal/SoundStream.h
	${VA_OPENAL_ROOT}/include/vaOpenal/stb_vorbis.h
	${VA_OPENAL_ROOT}/include/vaOpenal/Types.h
	
	${VA_OPENAL_ROOT}/src/AudioDevice.cpp
	${VA_OPENAL_ROOT}/src/AudioResource.cpp
	${VA_OPENAL_ROOT}/src/Listener.cpp
	${VA_OPENAL_ROOT}/src/Music.cpp
	${VA_OPENAL_ROOT}/src/Sound.cpp
	${VA_OPENAL_ROOT}/src/SoundBuffer.cpp
	${VA_OPENAL_ROOT}/src/SoundFile.cpp
	${VA_OPENAL_ROOT}/src/SoundFileDefault.cpp
	${VA_OPENAL_ROOT}/src/SoundFileOgg.cpp
	${VA_OPENAL_ROOT}/src/SoundPlayer.cpp
	${VA_OPENAL_ROOT}/src/SoundStereo.cpp
	${VA_OPENAL_ROOT}/src/SoundStream.cpp
	${VA_OPENAL_ROOT}/src/stb_vorbis.c
)


# -----< Platform specifics >
IF(UNIX)
IF(APPLE)
	# OSX
	
	# include directories for vaOpenal
	SET( VA_OPENAL_INCLUDES
	  ${VA_OPENAL_ROOT}/include
	  ${VA_OPENAL_ROOT}/libs/sndfile-osx/include 
	)
	SET( VA_OPENAL_INCLUDES  ${VA_OPENAL_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENAL_INCLUDES} )
		
	FIND_LIBRARY( COREAUDIO_LIBRARY CoreAudio )
	FIND_LIBRARY( OPENAL_LIBRARY OpenAL )
	MARK_AS_ADVANCED( COREAUDIO_LIBRARY  OPENAL_LIBRARY )
			
	# set target link libs for addon
	SET( VA_OPENAL_LINK_LIBRARIES
		${COREAUDIO_LIBRARY}	
		${OPENAL_LIBRARY}
		${VA_OPENAL_ROOT}/libs/sndfile-osx/lib/libsndfile.a
	)
	SET( VA_OPENAL_LINK_LIBRARIES  ${VA_OPENAL_LINK_LIBRARIES}  PARENT_SCOPE )
	
ELSE()
	# Linux
	
	# include directories for vaOpenal
	SET( VA_OPENAL_INCLUDES
	  ${VA_OPENAL_ROOT}/include
	  ${VA_OPENAL_ROOT}/libs/sndfile-linux/include 
	)
	SET( VA_OPENAL_INCLUDES  ${VA_OPENAL_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENAL_INCLUDES} )
		
	# set target link libs for addon
	SET( VA_OPENAL_LINK_LIBRARIES
		asound
	)
	SET( VA_OPENAL_LINK_LIBRARIES  ${VA_OPENAL_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
	# Windows
	
	# include directories for vaOpenal
	SET( VA_OPENAL_INCLUDES
	  ${VA_OPENAL_ROOT}/include
	  ${VA_OPENAL_ROOT}/libs/openal-win32/include 
	  ${VA_OPENAL_ROOT}/libs/sndfile-win32/include 
	)
	SET( VA_OPENAL_INCLUDES  ${VA_OPENAL_INCLUDES}  PARENT_SCOPE )
	INCLUDE_DIRECTORIES( ${VA_OPENAL_INCLUDES} )
		
	# set target link libs for addon
	SET( VA_OPENAL_LINK_LIBRARIES
		winmm.lib	
		${VA_OPENAL_ROOT}/libs/openal-win32/lib/OpenAL32.lib
		${VA_OPENAL_ROOT}/libs/sndfile-win32/lib/libsndfile-1.lib
	)
	SET( VA_OPENAL_LINK_LIBRARIES  ${VA_OPENAL_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF()
# -----</ Platform specifics>


TARGET_LINK_LIBRARIES( vaOpenal  
	va  ${VA_LINK_LIBRARIES}
	vaOpenal  ${VA_OPENAL_LINK_LIBRARIES}
)

SET_TARGET_PROPERTIES( vaOpenal PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_OPENAL_ROOT}/bin
)


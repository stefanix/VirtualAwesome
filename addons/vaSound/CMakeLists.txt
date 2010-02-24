

SET( VA_SOUND_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaSound )


#set includes, also make available in parent scope
SET( VA_SOUND_INCLUDES  ${VA_SOUND_ROOT}/include  ${VA_SOUND_ROOT}/libs/stk/include )
SET( VA_SOUND_INCLUDES  ${VA_SOUND_ROOT}/include  ${VA_SOUND_ROOT}/libs/stk/include  PARENT_SCOPE )

INCLUDE_DIRECTORIES( ${VA_SOUND_INCLUDES} )

	
ADD_LIBRARY( vaSound STATIC
	${VA_SOUND_ROOT}/include/vaSound/Sound.h
	${VA_SOUND_ROOT}/include/vaSound/EventHandlers.h
	${VA_SOUND_ROOT}/src/Sound.cpp

	${VA_SOUND_ROOT}/libs/stk/include/stk/ADSR.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Envelope.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/JetTable.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/PoleZero.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/StifKarp.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Asymp.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FM.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/LentPitShift.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/ReedTable.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Stk.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BandedWG.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FMVoices.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Mandolin.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Resonate.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TapDelay.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BeeThree.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FileLoop.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Mesh2D.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Rhodey.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TcpClient.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BiQuad.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FileRead.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Messager.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/RtAudio.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TcpServer.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Blit.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FileWrite.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/MidiFileIn.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/RtError.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Thread.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BlitSaw.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FileWvIn.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Modal.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/RtMidi.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TubeBell.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BlitSquare.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FileWvOut.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/ModalBar.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/RtWvIn.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TwoPole.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BlowBotl.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Filter.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Modulate.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/RtWvOut.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/TwoZero.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BlowHole.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Fir.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Moog.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/UdpSocket.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/BowTable.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Flute.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Mutex.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Vector3D.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Bowed.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/FormSwep.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/NRev.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Sampler.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/VoicForm.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Brass.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Function.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Noise.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Saxofony.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Voicer.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Chorus.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Generator.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/OnePole.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Shakers.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Whistle.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Clarinet.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Granulate.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/OneZero.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Simple.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Wurley.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Delay.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/HevyMetl.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/PRCRev.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/SineWave.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/SKINI.msg
	${VA_SOUND_ROOT}/libs/stk/include/stk/SKINI.tbl
	${VA_SOUND_ROOT}/libs/stk/include/stk/WvIn.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/DelayA.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Iir.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/PercFlut.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/SingWave.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/WvOut.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/DelayL.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/InetWvIn.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Phonemes.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Sitar.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Drummer.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/InetWvOut.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/PitShift.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Skini.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Echo.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Instrmnt.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/PluckTwo.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Socket.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Effect.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/JCRev.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Plucked.h
	${VA_SOUND_ROOT}/libs/stk/include/stk/Sphere.h
	
	${VA_SOUND_ROOT}/libs/stk/src/ADSR.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Granulate.cpp
	${VA_SOUND_ROOT}/libs/stk/src/RtAudio.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Asymp.cpp
	${VA_SOUND_ROOT}/libs/stk/src/HevyMetl.cpp
	${VA_SOUND_ROOT}/libs/stk/src/RtMidi.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BandedWG.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Iir.cpp
	${VA_SOUND_ROOT}/libs/stk/src/RtWvIn.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BeeThree.cpp
	${VA_SOUND_ROOT}/libs/stk/src/InetWvIn.cpp
	${VA_SOUND_ROOT}/libs/stk/src/RtWvOut.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BiQuad.cpp
	${VA_SOUND_ROOT}/libs/stk/src/InetWvOut.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Sampler.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Blit.cpp
	${VA_SOUND_ROOT}/libs/stk/src/JCRev.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Saxofony.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BlitSaw.cpp
	${VA_SOUND_ROOT}/libs/stk/src/LentPitShift.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Shakers.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BlitSquare.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Simple.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BlowBotl.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Mandolin.cpp
	${VA_SOUND_ROOT}/libs/stk/src/SineWave.cpp
	${VA_SOUND_ROOT}/libs/stk/src/BlowHole.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Mesh2D.cpp
	${VA_SOUND_ROOT}/libs/stk/src/SingWave.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Bowed.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Messager.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Sitar.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Brass.cpp
	${VA_SOUND_ROOT}/libs/stk/src/MidiFileIn.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Skini.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Chorus.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Modal.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Socket.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Clarinet.cpp
	${VA_SOUND_ROOT}/libs/stk/src/ModalBar.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Sphere.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Delay.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Modulate.cpp
	${VA_SOUND_ROOT}/libs/stk/src/StifKarp.cpp
	${VA_SOUND_ROOT}/libs/stk/src/DelayA.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Moog.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Stk.cpp
	${VA_SOUND_ROOT}/libs/stk/src/DelayL.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Mutex.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TapDelay.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Drummer.cpp
	${VA_SOUND_ROOT}/libs/stk/src/NRev.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TcpClient.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Echo.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Noise.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TcpServer.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Envelope.cpp
	${VA_SOUND_ROOT}/libs/stk/src/OnePole.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Thread.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FM.cpp
	${VA_SOUND_ROOT}/libs/stk/src/OneZero.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TubeBell.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FMVoices.cpp
	${VA_SOUND_ROOT}/libs/stk/src/PRCRev.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TwoPole.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FileLoop.cpp
	${VA_SOUND_ROOT}/libs/stk/src/PercFlut.cpp
	${VA_SOUND_ROOT}/libs/stk/src/TwoZero.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FileRead.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Phonemes.cpp
	${VA_SOUND_ROOT}/libs/stk/src/UdpSocket.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FileWrite.cpp
	${VA_SOUND_ROOT}/libs/stk/src/PitShift.cpp
	${VA_SOUND_ROOT}/libs/stk/src/VoicForm.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FileWvIn.cpp
	${VA_SOUND_ROOT}/libs/stk/src/PluckTwo.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Voicer.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FileWvOut.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Plucked.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Whistle.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Fir.cpp
	${VA_SOUND_ROOT}/libs/stk/src/PoleZero.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Wurley.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Flute.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Resonate.cpp
	${VA_SOUND_ROOT}/libs/stk/src/FormSwep.cpp
	${VA_SOUND_ROOT}/libs/stk/src/Rhodey.cpp
	
)


# -----< Platform specifics >
IF(UNIX)
IF(APPLE)
	# OSX
	
	ADD_DEFINITIONS( -D__MACOSX_CORE__ -D__LITTLE_ENDIAN__ )

	FIND_LIBRARY( COREAUDIO_LIBRARY CoreAudio )
	FIND_LIBRARY( COREMIDI_LIBRARY CoreMidi )
	MARK_AS_ADVANCED( COREAUDIO_LIBRARY  COREMIDI_LIBRARY )
			
	# set target link libs for addon
	SET( VA_SOUND_LINK_LIBRARIES
		${COREAUDIO_LIBRARY}	
		${COREMIDI_LIBRARY}	
	)
	SET( VA_SOUND_LINK_LIBRARIES  ${VA_SOUND_LINK_LIBRARIES}  PARENT_SCOPE )
	
ELSE()
	# Linux
	
	ADD_DEFINITIONS( -D__LINUX_ALSA__ -D__LINUX_ALSASEQ__ -D__LITTLE_ENDIAN__ )
	
	# set target link libs for addon
	SET( VA_SOUND_LINK_LIBRARIES
		asound
	)
	SET( VA_SOUND_LINK_LIBRARIES  ${VA_SOUND_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
	# Windows
	
	ADD_DEFINITIONS( -D__WINDOWS_DS__ -D__WINDOWS_MM__ -D__LITTLE_ENDIAN__ )
		
	# set target link libs for addon
	SET( VA_SOUND_LINK_LIBRARIES
		optimized  dsound.lib	
		optimized  winmm.lib	
		optimized  Wsock32.lib	
		debug  dsoundd.lib	
		debug  winmmd.lib	
		debug  Wsock32d.lib	
	)
	SET( VA_SOUND_LINK_LIBRARIES  ${VA_SOUND_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF()
# -----</ Platform specifics>


TARGET_LINK_LIBRARIES( vaSound  
	va  ${VA_LINK_LIBRARIES}
	vaSound  ${VA_SOUND_LINK_LIBRARIES}
)

SET_TARGET_PROPERTIES( vaSound PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_SOUND_ROOT}/bin
)


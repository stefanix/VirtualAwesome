

SET( VA_OSC_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaOsc )


#set includes, also make available in parent scope
SET( VA_OSC_INCLUDES  ${VA_OSC_ROOT}/include  ${VA_OSC_ROOT}/libs/oscpack/include )
SET( VA_OSC_INCLUDES  ${VA_OSC_ROOT}/include  ${VA_OSC_ROOT}/libs/oscpack/include  PARENT_SCOPE )

INCLUDE_DIRECTORIES( ${VA_OSC_INCLUDES} )

	
ADD_LIBRARY( vaOsc STATIC
	${VA_OSC_ROOT}/include/vaOsc/Arg.h
	${VA_OSC_ROOT}/include/vaOsc/Bundle.h
	${VA_OSC_ROOT}/include/vaOsc/EventHandlers.h
	${VA_OSC_ROOT}/include/vaOsc/Message.h
	${VA_OSC_ROOT}/include/vaOsc/Receiver.h
	${VA_OSC_ROOT}/include/vaOsc/Sender.h
	${VA_OSC_ROOT}/src/Bundle.cpp
	${VA_OSC_ROOT}/src/Message.cpp
	${VA_OSC_ROOT}/src/Receiver.cpp
	${VA_OSC_ROOT}/src/Sender.cpp

	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/IpEndpointName.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/MessageMappingOscPacketListener.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/NetworkingUtils.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscException.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscHostEndianness.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscOutboundPacketStream.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscPacketListener.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscPrintReceivedElements.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscReceivedElements.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/OscTypes.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/PacketListener.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/TimerListener.h
	${VA_OSC_ROOT}/libs/oscpack/include/oscpack/UdpSocket.h

	${VA_OSC_ROOT}/libs/oscpack/src/IpEndpointName.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/OscOutboundPacketStream.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/OscPrintReceivedElements.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/OscReceivedElements.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/OscTypes.cpp

	${VA_OSC_ROOT}/libs/oscpack/src/PosixNetworkingUtils.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/PosixUdpSocket.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/WinNetworkingUtils.cpp
	${VA_OSC_ROOT}/libs/oscpack/src/WinUdpSocket.cpp
		
)


# -----< Platform specifics >
IF(UNIX)
IF(APPLE)
	# OSX
			
	SET( VA_OSC_LINK_LIBRARIES
		
	)
	SET( VA_OSC_LINK_LIBRARIES  ${VA_OSC_LINK_LIBRARIES}  PARENT_SCOPE )
	
ELSE()
	# Linux

	SET( VA_OSC_LINK_LIBRARIES
		
	)
	SET( VA_OSC_LINK_LIBRARIES  ${VA_OSC_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
	# Windows

	SET( VA_OSC_LINK_LIBRARIES
        ws2_32.lib winmm.lib
	)
	SET( VA_OSC_LINK_LIBRARIES  ${VA_OSC_LINK_LIBRARIES}  PARENT_SCOPE )	
	
ENDIF()
# -----</ Platform specifics>


TARGET_LINK_LIBRARIES( vaOsc  
	va  ${VA_LINK_LIBRARIES}
	vaOsc  ${VA_OSC_LINK_LIBRARIES}
)

SET_TARGET_PROPERTIES( vaOsc PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_OSC_ROOT}/bin
)


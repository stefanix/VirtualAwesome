

SET( VA_NETWORK_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaNetwork )


#set includes, also make available in parent scope
SET( VA_NETWORK_INCLUDES  ${VA_NETWORK_ROOT}/include )
SET( VA_NETWORK_INCLUDES  ${VA_NETWORK_ROOT}/include PARENT_SCOPE )

INCLUDE_DIRECTORIES( ${VA_NETWORK_INCLUDES} )


# all source files
SET( VA_NETWORK_SOURCE
	${VA_NETWORK_ROOT}/include/vaNetwork/Config.h
	${VA_NETWORK_ROOT}/include/vaNetwork/EndPoint.h
	${VA_NETWORK_ROOT}/include/vaNetwork/EventHandlers.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Err.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Ftp.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Http.h
	${VA_NETWORK_ROOT}/include/vaNetwork/IpAddress.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Main.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Network.h
	${VA_NETWORK_ROOT}/include/vaNetwork/NonCopyable.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Packet.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Socket.h
	${VA_NETWORK_ROOT}/include/vaNetwork/SocketHandle.h
	${VA_NETWORK_ROOT}/include/vaNetwork/SocketImpl.h
	${VA_NETWORK_ROOT}/include/vaNetwork/SocketSelector.h
	${VA_NETWORK_ROOT}/include/vaNetwork/String.h
	${VA_NETWORK_ROOT}/include/vaNetwork/TcpListener.h
	${VA_NETWORK_ROOT}/include/vaNetwork/TcpSocket.h
	${VA_NETWORK_ROOT}/include/vaNetwork/UdpSocket.h
	${VA_NETWORK_ROOT}/include/vaNetwork/Utf.h

	${VA_NETWORK_ROOT}/src/EndPoint.cpp
	${VA_NETWORK_ROOT}/src/Err.cpp
	${VA_NETWORK_ROOT}/src/Ftp.cpp
	${VA_NETWORK_ROOT}/src/Http.cpp
	${VA_NETWORK_ROOT}/src/IpAddress.cpp
	${VA_NETWORK_ROOT}/src/Packet.cpp
	${VA_NETWORK_ROOT}/src/Socket.cpp
	${VA_NETWORK_ROOT}/src/SocketSelector.cpp
	${VA_NETWORK_ROOT}/src/String.cpp
	${VA_NETWORK_ROOT}/src/TcpListener.cpp
	${VA_NETWORK_ROOT}/src/TcpSocket.cpp
	${VA_NETWORK_ROOT}/src/UdpSocket.cpp
	${VA_NETWORK_ROOT}/src/Utf.cpp
)


# -----< Platform specifics >
IF( WINDOWS )
	SET( VA_NETWORK_SOURCE
	  ${VA_NETWORK_SOURCE}
		${VA_NETWORK_ROOT}/include/vaNetwork/SocketImplWin32.h
		${VA_NETWORK_ROOT}/src/SocketImplWin32.cpp
	)

	SET( VA_NETWORK_LINK_LIBRARIES ws2_32.lib )
	SET( VA_NETWORK_LINK_LIBRARIES  ${VA_NETWORK_LINK_LIBRARIES}  PARENT_SCOPE )	

ELSE()
	SET( VA_NETWORK_SOURCE
	  ${VA_NETWORK_SOURCE}
		${VA_NETWORK_ROOT}/include/vaNetwork/SocketImplUnix.h
		${VA_NETWORK_ROOT}/src/SocketImplUnix.cpp
	)
	
	SET( VA_NETWORK_LINK_LIBRARIES )
	SET( VA_NETWORK_LINK_LIBRARIES  ${VA_NETWORK_LINK_LIBRARIES}  PARENT_SCOPE )	
ENDIF()
# -----</ Platform specifics>


# make library from source files
ADD_LIBRARY( vaNetwork STATIC ${VA_NETWORK_SOURCE} )

# dependency libs
TARGET_LINK_LIBRARIES( vaNetwork  
	va  ${VA_LINK_LIBRARIES}
	vaNetwork  ${VA_NETWORK_LINK_LIBRARIES}
)

# where to put library
SET_TARGET_PROPERTIES( vaNetwork PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_NETWORK_ROOT}/bin
)


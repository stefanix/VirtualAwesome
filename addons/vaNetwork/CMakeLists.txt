
IF(APPLE)


SET( VA_NETWORK_ROOT  ${PROJECT_SOURCE_DIR}/addons/vaNetwork )

#set includes, also make available in parent scope
SET( VA_NETWORK_INCLUDES  ${VA_NETWORK_ROOT}/include )
SET( VA_NETWORK_INCLUDES  ${VA_NETWORK_ROOT}/include  PARENT_SCOPE )
INCLUDE_DIRECTORIES( ${VA_NETWORK_INCLUDES} )
	
ADD_LIBRARY( vaNetwork STATIC
	${VA_NETWORK_ROOT}/include/vaNetwork/Network.h
	${VA_NETWORK_ROOT}/include/vaNetwork/TCPClient.h
	${VA_NETWORK_ROOT}/include/vaNetwork/TCPManager.h
	${VA_NETWORK_ROOT}/include/vaNetwork/TCPServer.h
	${VA_NETWORK_ROOT}/include/vaNetwork/UDPManager.h

	${VA_NETWORK_ROOT}/src/TCPClient.cpp
	${VA_NETWORK_ROOT}/src/TCPManager.cpp
	${VA_NETWORK_ROOT}/src/TCPServer.cpp
	${VA_NETWORK_ROOT}/src/UDPManager.cpp
)					

TARGET_LINK_LIBRARIES( vaNetwork  
	va  ${VA_LINK_LIBRARIES}
	vaNetwork
)

SET_TARGET_PROPERTIES( vaNetwork PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_NETWORK_ROOT}/bin
)


ENDIF(APPLE)

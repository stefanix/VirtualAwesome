

SET( VA_MICE_ROOT ${PROJECT_SOURCE_DIR}/addons/vaMice )

#set includes, also make available in parent scope
SET( VA_MICE_INCLUDES  
	${VA_MICE_ROOT}/include  
	${VA_MICE_ROOT}/libs/manymouse
)
SET( VA_MICE_INCLUDES  
	${VA_MICE_ROOT}/include  
	${VA_MICE_ROOT}/libs/manymouse  
	PARENT_SCOPE
 )
INCLUDE_DIRECTORIES( ${VA_MICE_INCLUDES} )

	
ADD_LIBRARY( vaMice STATIC
	${VA_MICE_ROOT}/include/vaMice/Mice.h
	${VA_MICE_ROOT}/src/Mice.cpp
	
	${VA_MICE_ROOT}/libs/manymouse/linux_evdev.c
	${VA_MICE_ROOT}/libs/manymouse/macosx_hidmanager.c
	${VA_MICE_ROOT}/libs/manymouse/macosx_hidutilities.c
	${VA_MICE_ROOT}/libs/manymouse/manymouse.c
	${VA_MICE_ROOT}/libs/manymouse/manymouse.h
	${VA_MICE_ROOT}/libs/manymouse/windows_wminput.c
	${VA_MICE_ROOT}/libs/manymouse/x11_xinput.c	
)				

TARGET_LINK_LIBRARIES( vaMice  
	va  ${VA_LINK_LIBRARIES}
	vaMice
)

SET_TARGET_PROPERTIES( vaMice PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_MICE_ROOT}/bin
)

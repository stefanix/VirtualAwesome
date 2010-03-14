

SET( VA_TWEEN_ROOT ${PROJECT_SOURCE_DIR}/addons/vaTween )

#set includes, also make available in parent scope
SET( VA_TWEEN_INCLUDES  
	${VA_TWEEN_ROOT}/include  
)
SET( VA_TWEEN_INCLUDES  
	${VA_TWEEN_ROOT}/include  
	PARENT_SCOPE
 )
INCLUDE_DIRECTORIES( ${VA_TWEEN_INCLUDES} )

	
ADD_LIBRARY( vaTween STATIC
	${VA_TWEEN_ROOT}/include/vaTween/CppTweener.h
	${VA_TWEEN_ROOT}/src/CppTweener.cpp
)				

TARGET_LINK_LIBRARIES( vaTween  
	va  ${VA_LINK_LIBRARIES}
	vaTween
)

SET_TARGET_PROPERTIES( vaTween PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY  ${VA_TWEEN_ROOT}/bin
)
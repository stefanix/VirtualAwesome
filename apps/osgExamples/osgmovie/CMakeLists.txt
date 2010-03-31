
# Set the name and the root directory of this example.
# NOTE: Also make sure you add this subdirectory to the end
# of the master CMakeLists.txt in the root of VirtualAwesome
#
SET( EXAMPLE_NAME osgmovie )
SET( EXAMPLE_ROOT ${PROJECT_SOURCE_DIR}/apps/osgExamples/${EXAMPLE_NAME} )


# List all the  files belonging to this example
#
ADD_EXECUTABLE( ${EXAMPLE_NAME}  ${EXECUTABLE_TYPE}  
    ${EXAMPLE_ROOT}/src/main.cpp 
)


# List all the libraries to link against
# most core libs are already in VA_LINK_LIBRARIES
# otherwise simply list them afterwards separated by spaces
#
TARGET_LINK_LIBRARIES( ${EXAMPLE_NAME}
	${VA_LINK_LIBRARIES}
)


# Define the output path for the executable
# Please note that some IDEs add a "Release" or "Debug" to this
#
SET_TARGET_PROPERTIES( ${EXAMPLE_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY  ${EXAMPLE_ROOT}/bin
)

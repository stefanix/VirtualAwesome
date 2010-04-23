
# Set the name and the root directory of this example.
# NOTE: Also make sure you add this subdirectory to the end
# of the master CMakeLists.txt in the root of VirtualAwesome
#
SET( EXAMPLE_NAME exampleOscReceiver )
SET( EXAMPLE_ROOT ${PROJECT_SOURCE_DIR}/apps/addonExamples/${EXAMPLE_NAME} )

# List all the  files belonging to this example
#
ADD_EXECUTABLE( ${EXAMPLE_NAME}  ${EXECUTABLE_TYPE}  
    ${EXAMPLE_ROOT}/src/main.cpp
    ${EXAMPLE_ROOT}/src/MyApp.h 
    ${EXAMPLE_ROOT}/src/MyApp.cpp
)


# Set additional Include path
INCLUDE_DIRECTORIES( ${VA_OSC_INCLUDES} )


# List all the libraries to link against
# most core libs are already in VA_LINK_LIBRARIES
# otherwise simply list them afterwards separated by spaces
#
TARGET_LINK_LIBRARIES( ${EXAMPLE_NAME}  
	va  ${VA_LINK_LIBRARIES} 
	vaOsc  ${VA_OSC_LINK_LIBRARIES}
)


# Define the output path for the executable
# Please note that some IDEs add a "Release" or "Debug" to this
#
SET_TARGET_PROPERTIES( ${EXAMPLE_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY  ${EXAMPLE_ROOT}/bin
)

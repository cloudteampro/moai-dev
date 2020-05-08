cmake_minimum_required ( VERSION 2.8.5 )
project ( spine-v3 )


set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/3rdparty/spine_v3-c/" )
set ( SPINE_INCLUDES "${MOAI_ROOT}/3rdparty/spine_v3-c/include/" )

file ( GLOB_RECURSE SPINE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/spine/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/spine/*.h" 
)
file ( GLOB_RECURSE SPINE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/spine/*.h" )

add_library( spine-v3 STATIC ${SPINE_SOURCES} ${SPINE_HEADERS} )

target_include_directories ( spine-v3 PUBLIC "$<BUILD_INTERFACE:${SPINE_INCLUDES}>")
set_target_properties( spine-v3 PROPERTIES FOLDER Third-Party )
install(TARGETS spine-v3 EXPORT libmoai ARCHIVE DESTINATION lib)

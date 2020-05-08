cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-ct-util )

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/ct-util/" )

set ( MOAI_CTUTIL_INCLUDES 
  "${MOAI_ROOT}/src/"
  "${CMAKE_BINARY_DIR}/libmoai/config"
)

# Use all cpp files in directory as source code
file ( GLOB MOAI_CTUTIL_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
)

include_directories ( ${MOAI_CTUTIL_INCLUDES} )

add_library ( moai-ct-util STATIC ${MOAI_CTUTIL_SRC} )

set(BUILD_INCLUDES ${MOAI_CTUTIL_INCLUDES} )

target_include_directories (moai-ct-util PUBLIC 
    "$<BUILD_INTERFACE:${BUILD_INCLUDES}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
)

target_link_libraries ( moai-ct-util moai-sim moai-core moai-util zlcore sqlite3 )
set_target_properties(moai-ct-util PROPERTIES FOLDER Modules)

install(TARGETS moai-ct-util EXPORT libmoai ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/ct-util FILES_MATCHING PATTERN "*.h")

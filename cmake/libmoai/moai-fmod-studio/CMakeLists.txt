cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-fmod-studio )


set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/moai-fmod-studio/" )
set ( MOAI_FMOD_INCLUDES 
    "${MOAI_ROOT}/src/"
    "${CMAKE_BINARY_DIR}/libmoai/config/"
    "${MOAI_ROOT}/src/moai-fmod-studio/"
    "${MOAI_ROOT}/3rdparty/fmod-studio/headers/"
)

include_directories ( 
   ${MOAI_FMOD_INCLUDES}
)

# Use all cpp files in directory as source code
file ( GLOB MOAI_FMOD_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )


if ( BUILD_OSX )
  add_library(libfmod SHARED IMPORTED)
  set_property(TARGET libfmod PROPERTY IMPORTED_LOCATION ${MOAI_ROOT}/3rdparty/fmod-studio/lib/osx/libfmod.dylib)
endif ( BUILD_OSX )

if ( BUILD_IOS )
  add_library(libfmod STATIC IMPORTED)
  set_property(TARGET libfmod PROPERTY IMPORTED_LOCATION ${MOAI_ROOT}/3rdparty/fmod-studio/lib/ios/libfmod_iphoneos.a)
# libfmod_iphonesimulator.a
endif ( BUILD_IOS )

if ( BUILD_ANDROID )
  add_library(libfmod SHARED IMPORTED)
  set( FMOD_SHARED_LIB ${MOAI_ROOT}/3rdparty/fmod-studio/lib/android/${ANDROID_ABI}/libfmod.so )
  set_property(TARGET libfmod PROPERTY IMPORTED_LOCATION ${FMOD_SHARED_LIB})
endif ( BUILD_ANDROID )

# add_library ( moai-fmod-studio STATIC ${MOAI_FMOD_SRC} )
# target_include_directories( moai-fmod-studio PUBLIC ${MOAI_FMOD_INCLUDES})
# target_link_libraries (moai-fmod-studio libfmod moai-core moai-util moai-sim zlcore)

add_library ( moai-fmod-studio STATIC ${MOAI_FMOD_SRC} )
target_link_libraries (moai-fmod-studio moai-sim moai-core moai-util libfmod)

target_include_directories (moai-fmod-studio PUBLIC 
    "$<BUILD_INTERFACE:${MOAI_FMOD_INCLUDES}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/fmod-studio>"
)

set_target_properties(moai-fmod-studio PROPERTIES FOLDER Modules)  
install(TARGETS moai-fmod-studio EXPORT libmoai ARCHIVE DESTINATION lib)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/moai-fmod-studio FILES_MATCHING PATTERN "*.h")

if (BUILD_ANDROID)
  install(FILES ${FMOD_SHARED_LIB} DESTINATION lib)
endif(BUILD_ANDROID)

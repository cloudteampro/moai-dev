 project( luacmsgpack )
 
 set ( LUAEXT_SOURCES
      ${MOAI_ROOT}/3rdparty/lua-cmsgpack/lua_cmsgpack.c
 )
 
 add_library (luacmsgpack STATIC ${LUAEXT_SOURCES})
 LINK_DIRECTORIES("${LUA_LIB_DIR}")
 add_dependencies ( luacmsgpack liblua-static)
 target_include_directories ( luacmsgpack PUBLIC "$<BUILD_INTERFACE:${LUA_HEADERS}>")
 set_target_properties( luacmsgpack PROPERTIES FOLDER Third-Party )
 install(TARGETS luacmsgpack EXPORT libmoai ARCHIVE DESTINATION lib)
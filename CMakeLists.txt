cmake_minimum_required(VERSION 3.5)

project(dsvimlib)

set(CPACK_PACKAGE_NAME "dsvimlib")
set(CPACK_PACKAGE_VENDOR "WHOI DSL")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 3)
set(CPACK_SOURCE_GENERATOR "TXZ")
list(APPEND CPACK_SOURCE_IGNORE_FILES "^${CMAKE_SOURCE_DIR}/.git")
list(APPEND CPACK_SOURCE_IGNORE_FILES "^${CMAKE_SOURCE_DIR}/build[\\-_/]")
list(APPEND CPACK_SOURCE_IGNORE_FILES "^${CMAKE_BINARY_DIR}")
include(CPack)

set(DSVIMLIB_HEADERS
	include/convert.h
	include/ErrorCodeToMessage.h
	include/global.h
	include/imageA2b.h
	include/imageTalk.h
	include/IniFile.h
	include/launch_timer.h
	include/macros.h
	include/mkdir_p.h
	include/msg_util.h
	include/nio_thread.h
	include/time_util.h
	include/umcparameters.h
)

set(DSVIMLIB_SOURCES
	src/imageTalk.cpp
	src/IniFile.cpp
	src/launch_timer.cpp
	src/mkdir_p.cpp
	src/nio_thread.cpp
	src/time_util.cpp
	src/msg_util.cpp
)

add_library(dsvimlib SHARED ${DSVIMLIB_SOURCES})
set_target_properties(dsvimlib PROPERTIES PUBLIC_HEADER "${DSVIMLIB_HEADERS}")
install(TARGETS dsvimlib
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/dsvimlib
)
install(FILES dsvimlib-config.cmake DESTINATION lib/cmake/dsvimlib)


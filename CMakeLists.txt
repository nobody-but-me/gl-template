
cmake_minimum_required(VERSION 3.21)
project(PROJECT_NAME CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/core/libs/glm/
	${CMAKE_SOURCE_DIR}/core/libs/
	${CMAKE_SOURCE_DIR}/core/
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/core/renderer/*.cpp
	${CMAKE_SOURCE_DIR}/core/physics/*.cpp
	${CMAKE_SOURCE_DIR}/core/backend/*.cpp
	${CMAKE_SOURCE_DIR}/core/editor/*.cpp
	${CMAKE_SOURCE_DIR}/core/utils/*.cpp
	${CMAKE_SOURCE_DIR}/core/audio/*.cpp
	${CMAKE_SOURCE_DIR}/core/files/*.cpp
	${CMAKE_SOURCE_DIR}/core/libs/*.cpp
	${CMAKE_SOURCE_DIR}/core/math/*.cpp
	
	${CMAKE_SOURCE_DIR}/game/player/*.cpp
	${CMAKE_SOURCE_DIR}/game/camera/*.cpp
	${CMAKE_SOURCE_DIR}/game/levels/*.cpp
	${CMAKE_SOURCE_DIR}/game/bugs/*.cpp
)
add_executable(EXECUTABLE_NAME ${CMAKE_SOURCE_DIR}/core/main.cpp ${SRC_FILES} ${CMAKE_SOURCE_DIR}/core/libs/glad.c)
target_compile_options(EXECUTABLE_NAME PRIVATE -Wall -Werror -Wno-unused-result -Wno-unknown-pragmas)
target_link_libraries(EXECUTABLE_NAME PRIVATE glfw ${CMAKE_DL_LIBS})


cmake_minimum_required(VERSION 3.21)
project(PROJECT_NAME CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(EXECUTABLE_NAME)

include_directories(
	${CMAKE_SOURCE_DIR}/core/libs/imgui/
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
	${CMAKE_SOURCE_DIR}/core/res/*.cpp
	
	${CMAKE_SOURCE_DIR}/game/player/*.cpp
	${CMAKE_SOURCE_DIR}/game/camera/*.cpp
	${CMAKE_SOURCE_DIR}/game/levels/*.cpp
	${CMAKE_SOURCE_DIR}/game/bugs/*.cpp
)

if (UNIX)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
    
    target_link_libraries(EXECUTABLE_NAME PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
endif()

find_package(OpenGL REQUIRED)

target_sources(EXECUTABLE_NAME PRIVATE ${CMAKE_SOURCE_DIR}/core/main.cpp ${SRC_FILES} ${CMAKE_SOURCE_DIR}/core/libs/glad.c)
target_link_libraries(EXECUTABLE_NAME PRIVATE ${OPENGL_gl_LIBRARY} glfw)

target_compile_options(EXECUTABLE_NAME PRIVATE -Wall -Werror -Wno-unused-result -Wno-unknown-pragmas)

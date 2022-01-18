cmake_minimum_required(VERSION 3.19)
project(HelloWorld LANGUAGES C CXX VERSION 0.0.1)

add_subdirectory(sdk)

add_library(${PROJECT_NAME} SHARED
	main.cpp
	samp-plugin-sdk/amxplugin.cpp
	samp-plugin-sdk/amxplugin2.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_include_directories(${PROJECT_NAME} PRIVATE
	pawn-natives
	samp-plugin-sdk
	samp-plugin-sdk/amx
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	SDK
)

if(UNIX AND NOT APPLE)
	add_compile_definitions(LINUX)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)
include(AMXConfig)
include(AddSAMPPlugin)

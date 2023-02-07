cmake_minimum_required(VERSION 3.15)
project(wlfnstn)


if (UNIX)
	add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wfatal-errors)
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#[[ STATIC SFML LIBRARY ]]
set(SFML_STATIC_LIBRARIES TRUE)


add_executable (assets_display src/utils/assets_display.cpp)

#create directory in the build folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/bmps)

# copy a single file to build folder
add_custom_command(TARGET assets_display POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/resources/bmps/mguard_s_1.bmp
		${CMAKE_BINARY_DIR}/resources/bmps/mguard_s_1.bmp)




if (UNIX) 
	target_include_directories(assets_display PRIVATE /usr/include/x86_64-linux-gnu /usr/local/include)
	target_link_libraries(assets_display sfml-graphics sfml-window sfml-system sfml-audio)
endif()





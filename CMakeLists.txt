cmake_minimum_required(VERSION 3.15)
project(wlfnstn)


if (UNIX)
	set(CMAKE_CXX_COMPILER "clang++-11")
	add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wfatal-errors)
endif()



set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if (LINUX) 
	find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

	message (STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
	target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR} /usr/include/x86_64-linux-gnu /usr/local/include)
	target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
endif()





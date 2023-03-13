#A minimum cmake to build a project using opengl y glfw

cmake_minimum_required(VERSION 3.15)
project(text_renderer)

#Set Clang as the compiler
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-11")


find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIBRARIES "glfw")

#file(GLOB SRC_FILES *.cpp)

#add glad.c
list(APPEND SRC_FILES glad.c)

add_executable(text_renderer 
	glad.c
	#text_renderer.cpp 
	shader.cpp 
	shader.h)


#add fatal-error flag to tartget text_renderer
target_compile_options(text_renderer PRIVATE -Wfatal-errors)
target_link_libraries(text_renderer -lglfw -ldl) # -lX11 -lpthread -lXrandr -lXi  -ldl) #${LIBRARIES} ${OPENGL_LIBRARIES} -ldl)#-lglut -lGL -lGLEW -lGLU -ldl)



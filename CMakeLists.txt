cmake_minimum_required(VERSION 3.16)
project(quantum LANGUAGES C)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "Prevents cmake -S. -B.")
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "Prevent writing files to CMAKE_SOURCE_DIR under configure")

file(GLOB sources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.c)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${sources})

target_include_directories(${PROJECT_NAME}
  PUBLIC
  	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

#target_compile_features(${PROJECT_NAME} PRIVATE gnu_std_99)

target_compile_options(${PROJECT_NAME} PUBLIC -W)



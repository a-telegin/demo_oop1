cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "constructor")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wundef -Wno-missing-field-initializers")

add_executable(constructor
	${CMAKE_CURRENT_SOURCE_DIR}/src/constructor.cpp
	)

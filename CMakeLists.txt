cmake_minimum_required(VERSION 3.10)

project(tryStdInOut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tryStdInOut
	main.cpp
	)


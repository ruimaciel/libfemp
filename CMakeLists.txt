cmake_minimum_required(VERSION 3.1)

project(libfemp
	LANGUAGES CXX
	VERSION 0.1.0
	)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


option(USES_RE2C "Uses re2c to regenerate the lexer files")
option(BUILD_TESTING "Determines whether tests should be configured" ON )
option(LIBFEMP_BUILD_TESTING "Determines whether libfemp's tests should be configured" ON)

if(USES_RE2C)
	message(STATUS "Adding re2c custom rules")
	find_program(RE2C re2c REQUIRED)

	add_custom_command( OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/io/import/FemJsonParser.c++
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/io/import/FemJsonParser.cpp.re2c ${CMAKE_CURRENT_SOURCE_DIR}/src/io/import/FemJsonParser.hpp
		COMMAND ${RE2C}
		ARGS -i -T -o ${CMAKE_CURRENT_SOURCE_DIR}/src/io/import/FemJsonParser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/io/import/FemJsonParser.cpp.re2c
		COMMENT "Generating re2c files"
		)
else(USES_RE2C)
	message(STATUS "Skipping re2c custom rules")
endif()

find_package(Eigen3 3.3 REQUIRED)
find_package(Boost 1.71 REQUIRED COMPONENTS headers)
find_package(suitesparse MODULE REQUIRED)

add_subdirectory(libs)
add_subdirectory(src)

if(BUILD_TESTING AND LIBFEMP_BUILD_TESTING)
	find_package(GTest CONFIG REQUIRED)

	enable_testing()
	add_subdirectory(tests)
endif()

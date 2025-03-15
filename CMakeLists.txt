cmake_minimum_required(VERSION 3.25)
project("logfind")

include(CTest)

add_executable(logfind src/main.c
		       src/search/search.c
		       src/parameters/parameters.c)
target_include_directories(logfind PUBLIC src
					  src/search
					  src/parameters)

add_subdirectory(src/Unity)

# Tests
add_executable(test_parameters src/parameters/test/test_parameters.c
			       src/parameters/parameters.c)
target_link_libraries(test_parameters unity)
target_include_directories(test_parameters PUBLIC src/parameters
						  src/Unity)
add_test(NAME test_parameters COMMAND test_parameters)

cmake_minimum_required(VERSION 3.25)
project("greplog")

include(CTest)

add_executable(greplog src/main.c
		       src/search/search.c
		       src/parameters/parameters.c)
target_include_directories(greplog PUBLIC src
					  src/search
					  src/parameters)

add_subdirectory(src/Unity)

# Tests
add_executable(test_parameters src/parameters/test/test_parameters.c
			       src/parameters/parameters.c)
target_link_libraries(test_parameters unity)
target_include_directories(test_parameters PUBLIC src
						  src/parameters
						  src/Unity)
add_test(NAME test_parameters COMMAND test_parameters)

add_executable(test_search     src/search/test/test_search.c
			       src/search/search.c
		       	       src/parameters/parameters.c)
target_link_libraries(test_search unity)
target_include_directories(test_search PUBLIC src
					      src/search
					      src/Unity)
add_test(NAME test_search COMMAND test_search)

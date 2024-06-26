add_library(src SHARED load.cpp check_solution.cpp change_variable.cpp)
add_definitions( -std=c++14 -Wall )
target_include_directories(src PUBLIC ../inc)

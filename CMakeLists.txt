cmake_minimum_required(VERSION 3.0.0)
project(evrp VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(lib)

# add_executable(evrp EVRP.cpp stats.cpp HMAGS.cpp GreedySearch.cpp individual.cpp utils.cpp main.cpp)
add_executable(evrp main.cpp)
target_link_libraries(evrp PRIVATE evrp_lib_builder)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

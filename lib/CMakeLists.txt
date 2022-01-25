
include_directories(include)

add_library(
    evrp_lib_builder
    include/EVRP.hpp
    src/EVRP.cpp 
    include/stats.hpp
    src/stats.cpp 
    include/individual.hpp
    src/individual.cpp
    include/Algorithms.hpp
    src/HMAGS.cpp 
    src/SACO.cpp 
    src/GreedySearch.cpp 
    src/SA.cpp 
    include/utils.hpp
    src/utils.cpp
)  # end of add_library

target_include_directories(evrp_lib_builder PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
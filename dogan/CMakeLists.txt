project(dogan
        VERSION 0.1
        DESCRIPTION "A Catan-like game"
        LANGUAGES CXX)


# Set compilation flags
add_compile_options(-Wall)

include_directories(include)

add_library(DoganExceptions INTERFACE)
target_include_directories(DoganExceptions INTERFACE include)

add_library(DoganConfigBuilder libs/Configuration/DoganConfigBuilder.cpp include/DoganConfigBuilder.h)
target_link_libraries(DoganConfigBuilder PUBLIC DoganExceptions enums)
target_link_libraries(DoganConfigBuilder PRIVATE DoganConfig Coordinate DoganVertex)

add_library(DoganGame libs/DoganGame.cpp include/DoganGame.h)
target_link_libraries(DoganGame PUBLIC DoganExceptions)
target_link_libraries(DoganGame PRIVATE DoganBank DoganBoard DoganBuilding DoganPlayer DoganRoad DoganConfig)

add_subdirectory(libs)
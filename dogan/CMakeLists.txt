project(dogan
        VERSION 0.1
        DESCRIPTION "A Catan-like game"
        LANGUAGES CXX)


# Set compilation flags
add_compile_options(-Wall)

include_directories(include)

add_library(Exceptions INTERFACE)
target_include_directories(Exceptions INTERFACE include)

add_library(ConfigBuilder libs/Configuration/ConfigBuilder.cpp include/DoganConfigBuilder.h)
target_link_libraries(ConfigBuilder PUBLIC Exceptions enums)
target_link_libraries(ConfigBuilder PRIVATE Config Coordinate)

add_library(Game libs/Game.cpp include/DoganGame.h)
target_link_libraries(Game PUBLIC Exceptions)
target_link_libraries(Game PRIVATE Bank Board Building Player Config enums)

add_subdirectory(libs)
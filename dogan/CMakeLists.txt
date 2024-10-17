project(dogan
        VERSION 0.1
        DESCRIPTION "A Catan-like game"
        LANGUAGES CXX)


# Set compilation flags
add_compile_options(-Wall)

include_directories(libs)

add_library(DoganExceptions INTERFACE)
target_include_directories(DoganExceptions INTERFACE .)

add_subdirectory(libs)
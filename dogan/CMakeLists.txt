project(dogan
        VERSION 0.1
        DESCRIPTION "A Catan-like game"
        LANGUAGES CXX)


# Set compilation flags
add_compile_options(-Wall)

add_subdirectory(src)

option(BUILD_EXECUTABLE "Build the executable" ON)

if(BUILD_EXECUTABLE)
    add_executable(dogan src/main.cpp)
    target_link_libraries(dogan PUBLIC DoganGame DoganConfig)
else()
    add_library(dogan DoganGame)
endif()

# Now simply link against gtest or gtest_main as needed. Eg
# target_link_libraries(example gtest_main)
# add_test(NAME example_test COMMAND example)


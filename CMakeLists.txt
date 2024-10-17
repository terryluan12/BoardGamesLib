cmake_minimum_required(VERSION 3.22..3.30)
project(Dogan
		VERSION 0.1
		DESCRIPTION "A Collection of Games in C++"
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)									# Set C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)							# If the compiler does not support the standard, throw an error
set(CMAKE_CXX_EXTENSIONS OFF)								# Set C++ standard instead of G++

set_property(GLOBAL PROPERTY USE_FOLDERS ON)				# Use folders in IDEs

 # Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

include_directories(src)

add_subdirectory(src)
add_subdirectory(dogan)


option(BUILD_EXECUTABLE "Build the executable" ON)
option(BUILD_UNITTESTS "Build tests" ON)
if(BUILD_EXECUTABLE)
    add_executable(Dogan dogan/src/main.cpp)
    target_link_libraries(Dogan PUBLIC DoganGame DoganConfig)
    target_include_directories(Dogan PUBLIC dogan/include PRIVATE dogan/libs)
endif()

if(BUILD_UNITTESTS)
    enable_testing()
    add_executable(DoganTests dogan/libs/DoganBank.test.cpp)
    target_link_libraries(DoganTests gtest_main DoganBank)
    gtest_add_tests(TARGET DoganTests)
endif()

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
include_directories(include)
include_directories(dogan/libs)
include_directories(dogan/libs/Configuration)
include_directories(dogan/libs/GraphElements)
include_directories(dogan/libs/Structures)

add_subdirectory(src)
add_subdirectory(dogan)
add_subdirectory(docs)


option(BUILD_EXECUTABLE "Build the executable" ON)
if(BUILD_EXECUTABLE)
    add_executable(Dogan dogan/src/main.cpp)
    target_link_libraries(Dogan PUBLIC Game ConfigBuilder)
    target_include_directories(Dogan PUBLIC dogan/include PRIVATE dogan/libs)
endif()

# Tests
option(BUILD_UNITTESTS "Build tests" ON)
if(BUILD_UNITTESTS)
    enable_testing()
    add_executable(tests 
                  dogan/libs/Bank.test.cpp 
                  dogan/libs/Game.test.cpp
                  dogan/libs/Board.test.cpp
                  dogan/libs/Cell.test.cpp
                  src/AxialHexDirection.test.cpp)
    target_link_libraries(tests 
                  gtest_main 
                  gmock
                  Bank 
                  Game
                  ConfigBuilder
                  Board
                  AxialHexDirection
                  )
    gtest_add_tests(TARGET tests )
endif()

add_custom_target(format 
  COMMAND ${CMAKE_COMMAND} -E echo "Formatting using tools/format.sh"
  COMMAND ${PROJECT_SOURCE_DIR}/tools/format.sh ${PROJECT_SOURCE_DIR}/dogan ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include
)
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

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(src)
include_directories(include)
include_directories(dogan/include)
include_directories(dogan/libs)
include_directories(dogan/libs/Configuration)
include_directories(dogan/libs/GraphElements)
include_directories(dogan/libs/Structures)

add_subdirectory(src)
add_subdirectory(dogan)
add_subdirectory(docs)


option(BUILD_EXECUTABLE "Build the executable" ON)
# find_package(benchmark REQUIRED)
if(BUILD_EXECUTABLE)
    add_executable(Dogan dogan/src/main.cpp)
    target_link_libraries(Dogan 
                          PUBLIC Game 
                          PUBLIC ConfigBuilder)
                          # PRIVATE benchmark::benchmark)
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

find_package(SWIG 4.0 COMPONENTS python)

if(SWIG_FOUND)
  message("Found SWIG")
  include(${SWIG_USE_FILE})
  find_package(PythonLibs)
  include_directories(${PYTHON_INCLUDE_PATH})

  set_source_files_properties(dogan/extras/Dogan.i PROPERTIES CPLUSPLUS ON)
  swig_add_library( doganpython 
                    LANGUAGE python 
                    OUTPUT_DIR ${CMAKE_BINARY_DIR}/languages/python
                    OUTFILE_DIR ${CMAKE_BINARY_DIR}/languages/python
                    SOURCES 
                    dogan/extras/Dogan.i)
  
  # target_include_directories(doganpython PUBLIC ${PROJECT_SOURCE_DIR}/dogan/include PUBLIC ${PROJECT_SOURCE_DIR}/include)
  set_target_properties(doganpython PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/languages/python)
  target_link_libraries(doganpython ${PYTHON_LIBRARIES} ConfigBuilder CGame Config)

  
  set_source_files_properties(dogan/extras/enums.i PROPERTIES CPLUSPLUS ON)
  swig_add_library(dogan_enums 
                    LANGUAGE python 
                    OUTPUT_DIR ${CMAKE_BINARY_DIR}/languages/python
                    OUTFILE_DIR ${CMAKE_BINARY_DIR}/languages/python
                    SOURCES  
                    dogan/extras/enums.i)
    set_target_properties(dogan_enums PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/languages/python)
    target_link_libraries(dogan_enums ${PYTHON_LIBRARIES} enums)

  file(WRITE ${CMAKE_BINARY_DIR}/languages/python/__init__.py "")
endif()

add_custom_target(format 
  COMMAND ${CMAKE_COMMAND} -E echo "Formatting using tools/format.sh"
  COMMAND ${PROJECT_SOURCE_DIR}/tools/format.sh ${PROJECT_SOURCE_DIR}/dogan ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include
)
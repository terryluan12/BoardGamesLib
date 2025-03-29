cmake_minimum_required(VERSION 3.22..3.30)
project(Dogan
		VERSION 0.1
		DESCRIPTION "A Collection of Games in C++"
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)									# Set C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)							# If the compiler does not support the standard, throw an error
set(CMAKE_CXX_EXTENSIONS OFF)								# Set C++ standard instead of G++

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)				# Use folders in IDEs

 # Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/6910c9d9165801d8827d628cb72eb7ea9dd538c5.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
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
                  src/HexGame/Edge.test.cpp
                  src/HexGame/Vertex.test.cpp
                  dogan/libs/Bank.test.cpp 
                  dogan/libs/Game.test.cpp
                  dogan/libs/Board.test.cpp
                  dogan/libs/Cell.test.cpp
                  dogan/libs/Configuration/ConfigBuilder.test.cpp)
    target_link_libraries(tests 
                  gtest_main 
                  gmock
                  Bank 
                  Game
                  ConfigBuilder
                  Config
                  Board
                  )
    gtest_add_tests(TARGET tests )
endif()

# Set to local swig executable if necessary
set(SWIG_EXECUTABLE "/usr/local/bin/swig")

find_package(SWIG 4.4.0 COMPONENTS python go)

if(SWIG_FOUND)
  message("Found SWIG v${SWIG_VERSION}")
  include(${SWIG_USE_FILE})
  find_package(PythonLibs)
  include_directories(${PYTHON_INCLUDE_PATH})

  set_source_files_properties(dogan/extras/python/dogan.i PROPERTIES CPLUSPLUS ON)
  swig_add_library( doganpython 
                    LANGUAGE python 
                    OUTPUT_DIR ${CMAKE_BINARY_DIR}/languages/python
                    OUTFILE_DIR ${CMAKE_BINARY_DIR}/languages/python
                    SOURCES 
                    dogan/extras/python/dogan.i)
  
  # target_include_directories(doganpython PUBLIC ${PROJECT_SOURCE_DIR}/dogan/include PUBLIC ${PROJECT_SOURCE_DIR}/include)
  set_target_properties(doganpython PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/languages/python)
  target_link_libraries(doganpython ${PYTHON_LIBRARIES} ConfigBuilder Game Config AxialDirection)

  file(WRITE ${CMAKE_BINARY_DIR}/languages/python/__init__.py "")

  # Golang conversion
  find_program(GO_EXECUTABLE go)

  if (GO_EXECUTABLE)
    message("Using ${GO_EXECUTABLE} for generating Go Bindings")

    set_property(SOURCE dogan/extras/go/dogan.i PROPERTY CPLUSPLUS ON)

    swig_add_library(dogango
      TYPE SHARED
      LANGUAGE go
      OUTPUT_DIR ${CMAKE_BINARY_DIR}/languages/go
      OUTFILE_DIR ${CMAKE_BINARY_DIR}/languages/go
      SOURCES dogan/extras/go/dogan.i
      )
      target_link_libraries(dogango enums ConfigBuilder Game Config)

      execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
        /path/to/target_directory ${CMAKE_BINARY_DIR}/languages/go/src)

      file(WRITE ${CMAKE_BINARY_DIR}/languages/go/go.mod "module dogan\n\ngo 1.23.2")
  endif()

endif()

add_custom_target(format 
  COMMAND ${CMAKE_COMMAND} -E echo "Formatting using tools/format.sh"
  COMMAND ${PROJECT_SOURCE_DIR}/tools/format.sh ${PROJECT_SOURCE_DIR}/dogan ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include
)
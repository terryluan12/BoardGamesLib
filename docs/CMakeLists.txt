
find_package(Doxygen OPTIONAL_COMPONENTS dot)

option(BUILD_DOCS "Build Docs" ON)
if(BUILD_DOCS)
set(DOXYGEN_INPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
set(DOXYGEN_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${DOXYGEN_CONFIG_FILE} @ONLY)

doxygen_add_docs(docs
  ${DOXYGEN_INPUT_DIRECTORY}
  COMMENT "Generate documentation")
endif()
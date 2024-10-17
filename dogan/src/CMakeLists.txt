add_library(DoganBank DoganBank.cpp DoganBank.h)
target_link_libraries(DoganBank PUBLIC enums)

add_library(DoganBoard DoganBoard.cpp DoganBoard.h)
target_link_libraries(DoganBoard PUBLIC BoardInterface Coordinate DoganBank DoganCell DoganConfig DoganPlayer DoganPort DoganStructure DoganVertex)
target_link_libraries(DoganBoard PRIVATE Common)

add_library(DoganCell DoganCell.cpp DoganCell.h)
target_link_libraries(DoganCell PUBLIC CellInterface Coordinate enums)
target_link_libraries(DoganCell PRIVATE DoganEdge DoganVertex)

add_library(DoganConfig DoganConfig.cpp DoganConfig.h DoganConfigBuilder.cpp DoganConfigBuilder.h config.enum.h)
target_link_libraries(DoganConfig PUBLIC Common)
target_link_libraries(DoganConfig PRIVATE DoganPort DoganVertex enums)

add_library(DoganExceptions INTERFACE)
target_include_directories(DoganExceptions INTERFACE .)

add_library(DoganEdge DoganEdge.cpp DoganEdge.h)
target_link_libraries(DoganEdge PUBLIC Coordinate DoganCell enums)

add_library(DoganGame DoganGame.cpp DoganGame.h)
target_link_libraries(DoganGame PUBLIC DoganBank DoganBoard DoganPlayer DoganExceptions)

add_library(DoganPlayer DoganPlayer.cpp DoganPlayer.h)
target_link_libraries(DoganPlayer PUBLIC DoganBank DoganStructure)

add_library(DoganPort DoganPort.cpp DoganPort.h)
target_link_libraries(DoganPort PUBLIC DoganVertex enums)

add_library(DoganStructure DoganStructure.cpp DoganStructure.tpp DoganStructure.h)
target_link_libraries(DoganStructure PUBLIC DoganCell DoganEdge DoganVertex)

add_library(DoganVertex DoganVertex.cpp DoganVertex.h)
target_link_libraries(DoganVertex PUBLIC Coordinate enums)

add_library(enums enums.cpp enums.h)
target_link_libraries(enums PUBLIC HexagonalDirection Common)

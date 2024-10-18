add_subdirectory(Configuration)
add_subdirectory(GraphElements)
add_subdirectory(Structures)

add_library(DoganBank DoganBank.cpp DoganBank.h)
target_link_libraries(DoganBank PUBLIC enums)
target_link_libraries(DoganBank PRIVATE DoganExceptions)

add_library(DoganBoard DoganBoard.cpp DoganBoard.h)
target_link_libraries(DoganBoard PUBLIC BoardInterface DoganBank DoganCell DoganConfig DoganPlayer DoganPort DoganBuilding DoganRoad DoganStructure)
target_link_libraries(DoganBoard PRIVATE Common DoganCell)

add_library(DoganCell DoganCell.cpp DoganCell.h)
target_link_libraries(DoganCell PUBLIC CellInterface Coordinate enums)

add_library(DoganPlayer DoganPlayer.cpp DoganPlayer.h)
target_link_libraries(DoganPlayer PUBLIC DoganBank DoganBuilding DoganRoad DoganStructure)
target_link_libraries(DoganPlayer PRIVATE DoganExceptions)

add_library(DoganPort DoganPort.cpp DoganPort.h)
target_link_libraries(DoganPort PUBLIC DoganVertex enums)

add_library(enums enums.cpp enums.h)
target_link_libraries(enums PUBLIC AxialHexDirection Common)


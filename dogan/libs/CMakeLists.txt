add_subdirectory(Configuration)
add_subdirectory(GraphElements)
add_subdirectory(Structures)

add_library(Bank Bank.cpp Bank.h)
target_link_libraries(Bank PRIVATE Exceptions enums)

add_library(Board Board.cpp Board.h)
target_link_libraries(Board PUBLIC Bank Cell Config Player Building Structure)
target_link_libraries(Board PRIVATE Common ElementHelpers Cell)

add_library(Cell Cell.cpp Cell.h)
target_link_libraries(Cell PUBLIC Coordinate enums)

add_library(Player Player.cpp Player.h)
target_link_libraries(Player PUBLIC Bank Building Structure)
target_link_libraries(Player PRIVATE Exceptions)

add_library(enums enums.cpp)
target_link_libraries(enums PUBLIC AxialHexDirection Common)


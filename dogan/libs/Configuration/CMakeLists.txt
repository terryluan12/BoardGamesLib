add_library(Config Config.cpp config.enum.h defaultConfiguration.h)
target_link_libraries(Config PRIVATE Common enums)

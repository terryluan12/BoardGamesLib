add_library(DoganConfig DoganConfig.cpp config.enum.h defaultConfiguration.h)
target_link_libraries(DoganConfig PRIVATE Common enums)

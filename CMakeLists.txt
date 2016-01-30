project(SDL_Shownn)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sdl_shownn main.c)
install(TARGETS sdl_shownn DESTINATION bin)
target_link_libraries(sdl_shownn ${SDL2_LIBRARIES})

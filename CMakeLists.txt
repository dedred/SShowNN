project(SDL_Shownn)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

include_directories(/home/stu/docs/src/lwneuralnet-0.8/source)
link_directories(/home/stu/docs/src/lwneuralnet-0.8/source)
ADD_LIBRARY(lwneuralnet STATIC IMPORTED)
SET_TARGET_PROPERTIES(lwneuralnet PROPERTIES IMPORTED_LOCATION /home/stu/docs/src/lwneuralnet-0.8/source/liblwneuralnet.a)


add_executable(sdl_shownn render.c Log.c nnet.c main.c)
install(TARGETS sdl_shownn DESTINATION bin)
target_link_libraries(sdl_shownn lwneuralnet m ${SDL2_LIBRARIES})

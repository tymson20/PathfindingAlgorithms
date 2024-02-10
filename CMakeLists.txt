cmake_minimum_required(VERSION 3.14)

set(CXX_STANDARD 17)

project(PathfindingAlgorithms)

include_directories(${PROJECT_SOURCE_DIR}/libraries/SFML/include
                    ${PROJECT_SOURCE_DIR}/include)

set(SOURCES src/node.cpp src/grid.cpp)

add_executable(PathfindingAlgorithms main.cpp ${SOURCES})

target_link_libraries(PathfindingAlgorithms 
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/libsfml-graphics-s-d.a
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/libsfml-window-s-d.a
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/libsfml-system-s-d.a
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/libfreetype.a
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/opengl32.lib
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/gdi32.lib
        ${PROJECT_SOURCE_DIR}/libraries/SFML/lib/winmm.lib)
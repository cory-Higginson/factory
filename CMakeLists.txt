cmake_minimum_required(VERSION 3.14)
project(Factory)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif ()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES
        src/main.cpp
        src/State.h
        src/Game.cpp src/Game.h
        src/Placement.cpp src/Placement.h
        src/Builder.cpp src/Builder.h
        src/Objects/Chunk.cpp src/Objects/Chunk.h
        src/Objects/Block.cpp src/Objects/Block.h
        src/MapLoader.cpp src/MapLoader.h
        src/Conveyorlogic.cpp src/Conveyorlogic.h)

set(Helper_Files
        HelperFunctions/StaticFunctions.cpp
        HelperFunctions/StaticFunctions.h)

set(tinyxml2_Files
        tinyxml/tinyxml2.cpp
        tinyxml/tinyxml2.h)

add_executable(Factory ${SOURCE_FILES} ${Helper_Files} ${tinyxml2_Files})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries(Factory sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
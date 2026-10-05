cmake_minimum_required(VERSION 3.20)

project(Citadel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
)

FetchContent_MakeAvailable(SFML)

add_executable(Citadel
        main.cpp
        Grid.cpp
        Grid.h
)

target_link_libraries(Citadel PRIVATE
        SFML::Graphics
)
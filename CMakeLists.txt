cmake_minimum_required(VERSION 3.28)
project(PhysicSimulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)
add_executable(main 
src/action.cpp
src/collision.cpp
src/configuration.cpp
src/entity.cpp
src/game.cpp
src/main.cpp
src/player.cpp
src/shoot.cpp
src/shootPlayer.cpp
src/world.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SFML::Window)
target_link_libraries(main PRIVATE SFML::Audio)


cmake_minimum_required(VERSION 3.10)
project(GWBaseball2024)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(${PROJECT_NAME}
    Game.cpp
    Player.cpp
    PlayerManager.cpp
    GWBaseball2024.cpp
)

# Link SFML
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)
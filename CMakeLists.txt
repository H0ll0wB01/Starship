cmake_minimum_required(VERSION 3.19)
project(Starship VERSION 1.0)
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)

set(PROJECT_HEADERS 
include/Game.h
include/Bullet.h
include/Player.h
include/Enemy.h
include/DefaultEnemy.h
include/FastEnemy.h
include/TankEnemy.h
include/Bomb.h
)

set(PROJECT_SOURCES 
main.cpp
source/Game.cpp
source/Bullet.cpp
source/Player.cpp
source/Enemy.cpp
source/DefaultEnemy.cpp
source/TankEnemy.cpp
source/FastEnemy.cpp
source/Bomb.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include )

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
 SfmlWithCMake
 main.cpp
 ${PROJECT_FILES}
)

target_link_libraries(
 SfmlWithCMake
 sfml-graphics
 sfml-audio
 sfml-network
 sfml-system
 sfml-window
)

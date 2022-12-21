cmake_minimum_required(VERSION 3.2)

project(ROCKET_BATTLE
         VERSION 1.0
         DESCRIPTION "Arcade Rocket game mimic"
         LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "CMake Build Configuration for ${PROJECT_NAME} @v${PROJECT_VERSION}")

#executable 
add_executable(${PROJECT_NAME} src/main.cpp
                src/GameManager/GameManager.cpp
                src/GameManager/GGraphics.cpp
                src/GameManager/TextureManager.cpp
                src/GameManager/FileManager.cpp
                src/GameManager/LevelManager.cpp
                src/Entities/GameEntity.cpp
                src/Entities/Rocket.cpp
                src/Entities/Enemy.cpp
                src/Entities/Bullet.cpp
                src/Entities/EnemyManager.cpp
                src/Entities/BulletManager.cpp
                src/Entities/PowerUp.cpp
                src/Entities/PowerUpManager.cpp
                src/Entities/StatDrawer.cpp
                src/Controllers/KeyBoardHandler.cpp
                src/Screens/Screen.cpp
                src/Screens/HomeScreen.cpp
                src/Screens/MinScreen.cpp
                src/Screens/PauseScreen.cpp
                src/Utils/TimeSetting.cpp
                src/VectorMath/Vector2d.cpp)

#add include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2/include)

#add linked libraries depending on os
target_link_libraries(${PROJECT_NAME} PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2/lib/x64/SDL2_ttf.lib
                        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2/lib/x64/SDL2_image.lib
                        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2/lib/x64/SDL2.lib)

file(GLOB_RECURSE DLLS ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2/lib/x64/dlls/*.dll)


foreach(Dllfile ${DLLS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND "${CMAKE_COMMAND}" -E copy
                     ${Dllfile} ${CMAKE_CURRENT_SOURCE_DIR}/build)
endforeach()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}" -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/textures/ ${CMAKE_CURRENT_SOURCE_DIR}/build/textures
                    COMMENT "Copying textures")
#also move relevant dlls(based on os) to build folder for dynamic linking
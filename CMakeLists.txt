################################################################################
##               Copyright(c) 2013
## Filename        :    CMakeLists.txt
## Projectname     :    
## Author          :    Jujj
## Email           :    
## Date            :    周日 十二月  8 18:06:51 2013 (+0800)
## Version         :    v 1.0
## Description     :    
################################################################################
cmake_minimum_required(VERSION 2.6)

project(first-game)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/SDL1/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL1/lib/x86)

add_executable(first-game game.cpp gfx.cpp)
target_link_libraries(first-game SDL.lib SDLMain.lib)

add_executable(levelEditor levelEditor.cpp gfx.cpp)
target_link_libraries(levelEditor SDL.lib SDLMain.lib)

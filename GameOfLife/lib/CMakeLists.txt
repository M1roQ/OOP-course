
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Game-Of-Life)

add_library(GameOfLife STATIC
    GameEngine.cpp
    GameInterface.cpp
    GameState.cpp
    ParserCommandLine.cpp
    ParserCommands.cpp
    ParserFile.cpp
)

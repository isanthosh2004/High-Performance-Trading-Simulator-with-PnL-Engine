cmake_minimum_required(VERSION 3.10)

project(HFT_BACKTESTER VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(backtest
    src/main.cpp
    src/loader.cpp
    src/engine.cpp
    src/execution.cpp
    src/position.cpp
)

add_executable(csv2bin
    src/convert.cpp
    src/loader.cpp
)

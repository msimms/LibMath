cmake_minimum_required(VERSION 3.18.1)

project(libmath VERSION 1.0.0 DESCRIPTION "libmath")
include_directories(${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED
            BigInt.cpp
            Calculus.cpp
            Distance.cpp
            Double.cpp
            Graphics.cpp
            KMeans.cpp
            Matrix.cpp
            Peaks.cpp
            Powers.cpp
            Prime.cpp
            Signals.cpp
            SquareMatrix.cpp
            Statistics.cpp
            Vector.cpp
            main.cpp)
target_link_libraries(${PROJECT_NAME} "-pie -Wl,-E")
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)

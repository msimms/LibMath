cmake_minimum_required(VERSION 3.18.1)

project(libmath VERSION 1.0.0 DESCRIPTION "libmath")

file (GLOB_RECURSE Backend_SOURCES CONFIGURE_DEPENDS "*.cpp")
file (GLOB_RECURSE Backend_HEADERS CONFIGURE_DEPENDS "*.h")

add_library( # Sets the name of the library.
             libmath

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             main.cpp )

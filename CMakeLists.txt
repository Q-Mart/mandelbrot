cmake_minimum_required (VERSION 2.6)
project (Mandelbrot)
file (GLOB SOURCES "src/*.cpp")
add_executable (bin/Mandelbrot ${SOURCES})

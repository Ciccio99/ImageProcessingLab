cmake_minimum_required(VERSION 3.10)
project(Grad_Lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-2 -std=c++17 -Wall -Wextra -Weffc++ -pedantic -g")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Grad_Lab processImages.cpp ImageLoop.cpp ImageLoop.h ImageProcessor.cpp ImageProcessor.h Kernel.cpp Kernel.h)

target_link_libraries( Grad_Lab ${OpenCV_LIBS} )
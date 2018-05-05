# Image Processing Lab Assignment
Author: Alberto Scicali

## Goal
The goal of this lab is to learn how to use new, powerful frameworks and to 
learn how some of their functionalities are implemented.
You will create an application that will read in images and apply a
Local Mean Filter, a Gaussian Filter, and a custom made filter to the images.

## Installing OpenCV Instructions
WARNING: These instruction are for Unix based systems

```
mkdir OpenCV_Install && cd OpenCV_Install
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build && cd build
cmake - G "Unix Makefiles"
make -j8 //j# represents the number of cores (skip the flag to run openCV on a single core)
sudo make install
```

After the install is done you may need to logout/restart to create the symlinks
Once restarted, openCV should be ready to go!

## How to get OpenCV into your Clion c++ project
You need to tell clion to look for the directories with the necessary OpenCV files
Add these lines to you CMakeLists.txt

```
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( Grad_Lab ${OpenCV_LIBS} )
```

My Final CMakeLists.txt looks like this:
```
cmake_minimum_required(VERSION 3.10)
project(Grad_Lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-2 -std=c++17 -Wall -Wextra -Weffc++ -pedantic -g")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Grad_Lab processImages.cpp ImageLoop.cpp ImageLoop.h ImageProcessor.cpp ImageProcessor.h Kernel.cpp Kernel.h)

target_link_libraries( Grad_Lab ${OpenCV_LIBS} )
```

Once the CMakeLists.txt file is setup, you will be able to include the openCV header files into your program.

## OpenCV
All the openCV utilities can be found under the "cv" namespace.
The ones used in this program include:
- cv::imread | "Reads in an image file into a cv::Mat"
- cv::IMREAD_COLOR | "Enum used in cv::imread, tells the function what kind of picture is being loaded (Loads it in as a colored image)"
- cv::Mat | "A matrix object"
- cv::nameWindow | "Creates a new window with the given identifier"
- cv::WINDOW_AUTOSIZE | "Enum used when display an image"
- cv::imshow | "Function to show the provided image on the name window"
- cv::waitKey | "Waits for input or after a certain number of millisecond to allow display window to render"
- cv::Vec3b | "Vector that holds three bytes"
- cv::Vec3f | "Vector that holds three floats"

## Commands For Program
 * readImage: Read in the path to an image
 * displayImage: Displays the currently loaded image
 * applyMeanFilter: Displays a copy of the loaded image with a mean filter applied
 * applyGausFilter: Displays a copy of the loaded image with a guassian filter applied
 * applyCustomFilter: Displays a copy of the loaded image with a customer made filter applied

## Example of Finished Lab
### Click this to watch the video on youtube
(The video is also in the repository so that it can be viewed locally)
[![Watch the video](https://i.ytimg.com/vi/NoZvNBT5DFo/hqdefault.jpg?sqp=-oaymwEXCNACELwBSFryq4qpAwkIARUAAIhCGAE=&rs=AOn4CLDEBXZtP_Whj3CbGX7AFJ0ETS1-wA)](https://youtu.be/NoZvNBT5DFo)


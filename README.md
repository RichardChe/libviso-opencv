# libviso-opencv
libviso with opencv image interface

[libviso2](http://www.cvlibs.net/software/libviso/) is a open-source visual odometry inplemented in C++. The released version by A. Geiger uses libpng for image input. Here I simply use OpenCV interface when reading images for convenience.

## Dependencies
* OpenCV 2.4: follow the instructions on http://opencv.org/ or install 
  via 

        sudo apt-get install libopencv-dev
        
* CMake,

        sudo apt-get install cmake

## Installation(Tested in Ubuntu 14.04)
1. Clone this repository via 

        git clone https://github.com/Richardche/libviso-opencv.git

2. Build

        mkdir build && cd build
        cmake ..
        make

## Run
1.  Make sure the current directory is libviso-opencv/build
2. Copy a paramater file to libviso-opencv/build

        cp ../src/parameter.xml.example parameter.xml

3. Change the paths and frame begin and end in parameter.xml
4. run

        ./viso2 parameter.xml


# libviso-opencv
libviso with opencv image interface

![libviso2](http://www.cvlibs.net/software/libviso/) is a open-source visual odometry inplemented in C++. The released version by A. Geiger uses libpng for image input. Here I simply use OpenCV interface when reading images for convenience.

## Dependencies
* OpenCV 2.4-3.0: follow the instructions on http://opencv.org/ or install 
  via 

        sudo apt-get install libopencv-dev
  
* CMake,

        sudo apt-get install cmake
        
        
## Installation(Tested in Ubuntu 14.04)
1. Clone this repository via 

        git clone https://github.com/ethz-asl/okvis.git

2. Build

        mkdir build && cd build
        cmake ..
        make
      

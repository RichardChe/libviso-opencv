# project
cmake_minimum_required (VERSION 2.6)
project (libviso2)

#modified:use opencv instead of libpng for convenience
find_package(OpenCV REQUIRED)
#find_package(OpenGL REQUIRED)
# directories
set (LIBVISO2_SRC_DIR src)

# include directory
include_directories("${LIBVISO2_SRC_DIR}")

# use sse3 instruction set
SET(CMAKE_CXX_FLAGS "-msse3")

# sources
FILE(GLOB LIBVISO2_SRC_FILES "src/*.cpp")

# make release version
set(CMAKE_BUILD_TYPE Release)

# demo program
add_executable(viso2 ${LIBVISO2_SRC_FILES})
target_link_libraries (viso2 ${OpenCV_LIBS})


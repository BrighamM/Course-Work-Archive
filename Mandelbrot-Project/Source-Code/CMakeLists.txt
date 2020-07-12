cmake_minimum_required(VERSION 3.11.1)
project (Mandelbrot_PROJECT)


set(CMAKE_CXX_FLAGS "-std=c++17 -g0 -O3 -Wall -Wextra -Werror -I/usr/local/include  -L/usr/local/lib -lpng -lPNGwriter -lz -DNO_FREETYPE")

# Bring the header files into the project
include_directories(include)

#Can manually add the sources...
#set(SOURCES src/main.cpp src/Dragon.cpp)

# but lets make it easier...
file(GLOB SOURCES "src/*.cpp")

add_executable(Mand_Exe ${SOURCES})

find_package(PNGwriter 0.7.0)

if(PNGwriter_FOUND)
	  target_link_libraries(Mand_Exe PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)



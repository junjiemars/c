cmake_minimum_required(VERSION 3.0)
project(cxx_std14 LANGUAGES CXX)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# Add your source files
set(SOURCES
    main.cc
)

# Add your header files
#set(HEADERS
#)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

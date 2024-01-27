cmake_minimum_required(VERSION 3.0)
project(cxx_std20 LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
    main.cc
)

# Add your header files
#set(HEADERS
#)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

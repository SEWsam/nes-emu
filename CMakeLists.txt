cmake_policy(SET CMP0025 NEW)
cmake_minimum_required(VERSION 3.0.0)
project(NES-EMU VERSION 0.1.0)


include(CTest)
include(src/CMakeLists.txt)
enable_testing()

add_executable(NES-EMU ${SOURCES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

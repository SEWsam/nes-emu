cmake_policy(SET CMP0025 NEW)
cmake_minimum_required(VERSION 3.0.0)
project(NES-EMU VERSION 0.1.0)

include(CTest)
include(src/CMakeLists.txt)
include(test/CMakeLists.txt)
find_package(Catch2 REQUIRED)
enable_testing()

include_directories(include)

add_library(NES-EMU_CORE ${SOURCES})
add_executable(NES-EMU ${NES-EMU_MAIN})
target_link_libraries(NES-EMU NES-EMU_CORE)

add_executable(unit_tests ${TEST-SOURCES})
target_link_libraries(unit_tests NES-EMU_CORE Catch2::Catch2)

# Boost support
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS serialization) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(NES-EMU ${Boost_LIBRARIES})
    target_link_libraries(unit_tests ${Boost_LIBRARIES})
endif()

target_compile_definitions(NES-EMU PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

include(Catch)
catch_discover_tests(unit_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
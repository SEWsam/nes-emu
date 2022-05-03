include(${CMAKE_CURRENT_LIST_DIR}/debug/CMakeLists.txt)

list(APPEND SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/CPU.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/Opcode.cpp
)

set(NES-EMU_MAIN ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
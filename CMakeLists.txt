cmake_minimum_required (VERSION 2.6)
project (Pinedit)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(PINEDIT_EXEC_NAME pinedit)

add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(doc)

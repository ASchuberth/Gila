cmake_minimum_required(VERSION 3.5)

add_library(observerlib ${CMAKE_CURRENT_LIST_DIR}/observer.cpp
                        ${CMAKE_CURRENT_LIST_DIR}/subject.cpp)

target_include_directories(observerlib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

target_link_libraries(observerlib PRIVATE pch_interface)
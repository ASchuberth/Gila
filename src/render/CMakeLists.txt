cmake_minimum_required(VERSION 3.5)

add_library(renderlib ${CMAKE_CURRENT_LIST_DIR}/render.cpp
                                   ${CMAKE_CURRENT_LIST_DIR}/sketch.cpp 
                                   ${CMAKE_CURRENT_LIST_DIR}/model.cpp 
                                    )

target_include_directories(renderlib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)

target_link_libraries(renderlib PRIVATE pch_interface)
target_link_libraries(renderlib PRIVATE observerlib)
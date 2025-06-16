cmake_minimum_required(VERSION 3.26)


project(gila)





# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra") 

# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_executable(gila src/main.cpp
                    src/elements/spring.cpp)

add_subdirectory ("docs")

#=========================================
# Precompiled Headers / Include Directories
#=========================================

add_library(pch_interface INTERFACE)
target_precompile_headers(pch_interface INTERFACE src/pch.hpp) 
target_include_directories(pch_interface INTERFACE ${CMAKE_SOURCE_DIR}/src)

#=========================================
# Libraries
#=========================================


find_package(glm CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE glm::glm)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE Eigen3::Eigen)


# Precompiled Headers
target_link_libraries(gila PUBLIC pch_interface)
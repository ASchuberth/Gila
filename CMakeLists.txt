cmake_minimum_required(VERSION 3.8)


project(gila VERSION 0.1.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra") 

# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_executable(gila src/main.cpp
                    src/gila.cpp
                    src/elements/spring.cpp
                    )



#=========================================
# Precompiled Headers / Include Directories
#=========================================

add_library(pch_interface INTERFACE)
target_precompile_headers(pch_interface INTERFACE src/pch.hpp) 
target_include_directories(pch_interface INTERFACE ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src/observer)
add_subdirectory(src/render)
add_subdirectory ("docs")


#=========================================
# Libraries
#=========================================


find_package(glm CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE glm::glm)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE Eigen3::Eigen)

find_package(Vulkan REQUIRED)
target_link_libraries(pch_interface INTERFACE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(pch_interface INTERFACE imgui::imgui)

find_package(Stb REQUIRED)
target_include_directories(pch_interface INTERFACE ${Stb_INCLUDE_DIR})

# Precompiled Headers

target_link_libraries(gila PUBLIC pch_interface)

target_link_libraries(gila PUBLIC observerlib)
target_link_libraries(gila PUBLIC renderlib)


#=========================================
# Shaders
#=========================================

get_filename_component(VERT_SHADER_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/shaders/vert.spv ABSOLUTE)
get_filename_component(FRAG_SHADER_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/shaders/frag.spv ABSOLUTE)
configure_file(${CMAKE_CURRENT_LIST_DIR}/src/render/config.h.in ${CMAKE_CURRENT_LIST_DIR}/src/render/config.h)


# Compile Shaders

if(WIN32)
    execute_process(COMMAND ${CMAKE_CURRENT_LIST_DIR}/shaders/compile_shaders.bat ${CMAKE_CURRENT_LIST_DIR}/shaders/)
endif(WIN32)

if(UNIX)
    execute_process(COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/shaders/compile_shaders.sh ${CMAKE_CURRENT_LIST_DIR}/shaders/)
endif(UNIX)
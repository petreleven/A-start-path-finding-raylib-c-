cmake_minimum_required(VERSION 3.5)
project(main)

add_subdirectory(raylib)
add_subdirectory(imgui)
add_subdirectory(grid_node)

add_executable(main main.cpp Pathfinder.cpp)
target_link_libraries(main PUBLIC raylib imgui imgui_impl_glfw rlImGui Grid Node)
target_include_directories(main PUBLIC 
              "${PROJECT_BINARY_DIR}"
               "${PROJECT_SOURCE_DIR}/raylib"
              "${PROJECT_SOURCE_DIR}/imgui"
              "${PROJECT_SOURCE_DIR}/grid_node")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

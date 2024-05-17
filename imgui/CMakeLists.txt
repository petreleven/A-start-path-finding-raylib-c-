# Add the ImGui library and its dependencies
add_library(imgui
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp  # Add this line if tables are used
)
add_library(imgui_impl_glfw imgui_impl_glfw.cpp)

# Add the rlImGui library and link it with the ImGui and imgui_impl_glfw libraries
add_library(rlImGui rlImGui.cpp)
target_link_libraries(rlImGui PUBLIC imgui imgui_impl_glfw)

# Set include directories for rlImGui
target_include_directories(rlImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")


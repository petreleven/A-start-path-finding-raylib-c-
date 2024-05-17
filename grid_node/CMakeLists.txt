add_library(Grid Grid.cpp)
add_library(Node Node.cpp)

target_link_libraries(Grid PUBLIC Node)
target_include_directories(Grid PUBLIC "${CMAKE_CURRENT_DIR}")
target_include_directories(Node PUBLIC "${CMAKE_CURRENT_DIR}")

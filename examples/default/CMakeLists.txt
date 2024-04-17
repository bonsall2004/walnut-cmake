cmake_minimum_required(VERSION 3.20)
project(walnut-cmake-example)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES src/Entry.cpp)

add_executable(walnut-cmake-example ${SOURCES})

target_link_libraries(walnut-cmake-example PRIVATE Walnut)
target_include_directories(walnut-cmake-example PRIVATE includes ../../deps/imgui ../../deps/GLFW/include ../../deps/Walnut/Source ../../deps/Walnut/Platform/GUI C:/VulkanSDK/1.3.268.0/Include ../../deps/glm)
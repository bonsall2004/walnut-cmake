cmake_minimum_required(VERSION 3.20)
project(imgui)
set(LIB_NAME imgui)

set(CMAKE_CXX_STANDARD 20)

add_library(${LIB_NAME} STATIC imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp backends/imgui_impl_vulkan.cpp backends/imgui_impl_glfw.cpp)

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIB_NAME} PUBLIC ../imgui backends/ C:/VulkanSDK/1.3.268.0/Include ../GLFW/include)
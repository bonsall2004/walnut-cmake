cmake_minimum_required(VERSION 3.20)
project(Walnut)
set(LIB_NAME Walnut)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_library(${LIB_NAME} STATIC
        Source/Walnut/Random.cpp
        Source/Walnut/Utils/StringUtils.cpp
        Source/Walnut/Serialization/StreamReader.cpp
        Source/Walnut/Serialization/StreamWriter.cpp
        Source/Walnut/Serialization/BufferStream.cpp
        Source/Walnut/Serialization/FileStream.cpp
        Source/Walnut/Core/Log.cpp
        Platform/GUI/Walnut/ApplicationGUI.cpp
        Platform/GUI/Walnut/Image.cpp
        Platform/GUI/Walnut/UI/UI.cpp
        Platform/GUI/Walnut/UI/Console.cpp
        Platform/GUI/Walnut/Input/Input.cpp
        Platform/GUI/Walnut/ImGui/ImGuiBuild.cpp
        Platform/GUI/Walnut/ImGui/ImGuiTheme.cpp
        Platform/Headless/Walnut/ApplicationHeadless.cpp
)

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} PUBLIC Vulkan::Vulkan glfw imgui)
target_include_directories(${LIB_NAME} PUBLIC Source Platform/GUI ../GLFW/include ../stb_image C:/VulkanSDK/1.3.268.0/Include ../glm ../spdlog/include)

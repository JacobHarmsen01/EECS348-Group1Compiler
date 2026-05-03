cmake_minimum_required(VERSION 3.16)
project(ExpressionParser)

add_definitions(-DGL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ImGui sources
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

# Parser sources
set(PARSER_SOURCES
    src/lexer.cpp
    src/parser.cpp
    src/evaluator.cpp
    imgui/main.cpp
)

add_executable(ExpressionParser ${PARSER_SOURCES} ${IMGUI_SOURCES})

target_include_directories(ExpressionParser PRIVATE
    ${IMGUI_DIR}
    src/
)

target_link_libraries(ExpressionParser PRIVATE
    OpenGL::GL
    glfw
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

# Bundle as .app on Mac
set_target_properties(ExpressionParser PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "Expression Parser"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
)
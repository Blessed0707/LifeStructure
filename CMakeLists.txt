cmake_minimum_required(VERSION 3.10)
project(LifeStructure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ============================================================
# NEW: Pull in GLFW and Dear ImGui as dependencies
# ============================================================
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.0
)
FetchContent_MakeAvailable(imgui)

# ============================================================
# NEW: ImGui has no CMakeLists.txt of its own, so we build it
# ourselves as a small static library, including the GLFW +
# OpenGL3 backend files that live in ImGui's backends/ folder.
# ============================================================
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw)

# NEW: macOS/system OpenGL, needed by the OpenGL3 backend above
find_package(OpenGL REQUIRED)

# ============================================================
# EXISTING: unchanged from what you already had
# ============================================================

# Where to find cpp files
file(GLOB_RECURSE SOURCE "src/*.cpp")

# Creates the .exe
add_executable(LifeStructure ${SOURCE})

# Where to find headers
target_include_directories(LifeStructure PRIVATE
    src
    src/Core
    src/Entries
    src/TerminalUI
    src/Containers
    src/Utils
    src/Gui
    includes
)

# ============================================================
# NEW: link ImGui + OpenGL into your existing executable
# ============================================================
target_link_libraries(LifeStructure PRIVATE imgui OpenGL::GL)
cmake_minimum_required(VERSION 3.10)
project(LifeStructure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Where to find cpp files
file(GLOB_RECURSE SOURCE "src/*.cpp")

# Creates the .exe
add_executable(LifeStructure ${SOURCE})

# Where to find headers
target_include_directories(LifeStructure PRIVATE
    src
    src/Core
    src/JournalEntry
    src/TerminalUI
    src/Containers
    src/Utils
    includes
)
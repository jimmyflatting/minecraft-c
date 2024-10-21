cmake_minimum_required(VERSION 3.10)
project(minecraft_clone C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C standard and compiler options
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fbracket-depth=1024")

# Set include directories
include_directories(lib/cglm/include lib/glad/include lib/glfw/include lib/stb lib/noise src/ecs)

# Add external libraries
add_subdirectory(lib/cglm)
add_subdirectory(lib/glfw)

# Add glad as a static library
add_library(glad STATIC lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)

# Locate all source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Create an executable
add_executable(game ${SOURCES})

# Link external libraries
target_link_libraries(game cglm glfw glad m)

# Platform-specific linking for macOS and Linux
if(APPLE)
    target_link_libraries(game
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework Cocoa"
    )
elseif(UNIX)
    target_link_libraries(game dl pthread)
endif()

# Set the output directory
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Custom build step for creating the bin directory
add_custom_command(
    TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin"
)

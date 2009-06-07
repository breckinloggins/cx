# The root of the project directory is ${CX_SOURCE_DIR}
# The binary directory is ${CX_BINARY_DIR}
cmake_minimum_required(VERSION 2.6)
project(CX)

add_subdirectory(common)
add_subdirectory(ast)

# Define the cxc executable for our compiler
add_executable(cxc cxc.c)

target_link_libraries(cxc common ast)
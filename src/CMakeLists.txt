# The root of the project directory is ${CX_SOURCE_DIR}
# The binary directory is ${CX_BINARY_DIR}
cmake_minimum_required(VERSION 2.6)
project(CX)

set(Cx_SRCS base.c ast.c identifier_table.c cxc.c context_visitor.c c_codegen_visitor.c graphprinter_visitor.c)

add_subdirectory(common)

# Create a target for the parser
add_custom_target(CxParser echo "Creating Cx Parser")

# Create a custom command for bison
add_custom_command(
	SOURCE ${CX_SOURCE_DIR}/parser.y
	COMMAND bison
	ARGS -y ${CX_SOURCE_DIR}/parser.y -o ${CX_BINARY_DIR}/parser.c
	TARGET CxParser
	OUTPUTS ${CX_BINARY_DIR}/parser.c ${CX_SOURCE_DIR}/parser.h 
)

# Create custom command for flex
add_custom_command(
	SOURCE ${CX_SOURCE_DIR}/scanner.l
	COMMAND flex
	ARGS -o ${CX_BINARY_DIR}/scanner.c ${CX_SOURCE_DIR}/scanner.l
	TARGET CxParser
	OUTPUTS ${CX_BINARY_DIR}/scanner.c
)

set(Cx_SRCS ${Cx_SRCS} ${CX_BINARY_DIR}/scanner.c)
set(Cx_SRCS ${Cx_SRCS} ${CX_BINARY_DIR}/parser.c)

set_source_files_properties(${CX_BINARY_DIR}/parser.c GENERATED)
set_source_files_properties(${CX_BINARY_DIR}/scanner.c GENERATED)
set_source_files_properties(${CX_SOURCE_DIR}/ast.c OBJECT_DEPENDS ${CX_BINARY_DIR}/parser.h)

# parser.h is here
include_directories(${CX_BINARY_DIR})

# and everything else is here
include_directories(${CX_SOURCE_DIR} ${CX_SOURCE_DIR}/common)

# Define the cxc executable for our compiler
add_executable(cxc ${Cx_SRCS})

target_link_libraries(cxc common)
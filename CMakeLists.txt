# CMake settings
cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)

# Project settings
project(rdr2_mouse_pointer_fix C CXX)
set(ROOT ${PROJECT_SOURCE_DIR})

# File list: required for IDE project structure generation
file(GLOB RDR2_MOUSE_IMPLEMENTATION_SRC ${ROOT}/fix/*.h ${ROOT}/fix/*.cpp)

# All sources
set(PROJECT_SRC
	${RDR2_MOUSE_IMPLEMENTATION_SRC}
)

# IDE filters
source_group("rdr2_mouse" FILES ${RDR2_MOUSE_IMPLEMENTATION_SRC})

# Visual Studio startup project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT rdr2_mouse)

# Includes
set(PROJECT_INCLUDE_DIRS
	${PROJECT_INCLUDE_DIRS}
	${ROOT}/fix
)

# Project binary
add_executable(rdr2_mouse WIN32 ${PROJECT_SRC})

target_include_directories(rdr2_mouse PRIVATE ${PROJECT_INCLUDE_DIRS})
target_compile_definitions(rdr2_mouse PRIVATE _SCL_SECURE_NO_WARNINGS)
target_compile_options(rdr2_mouse PRIVATE "/MP")

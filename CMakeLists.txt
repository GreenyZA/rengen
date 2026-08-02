cmake_minimum_required(VERSION 3.16)
project(rengen
    VERSION 0.1.0
    DESCRIPTION "A CPU-based 3D graphics rendering engine for learning lighting, reflections, and deep shadows"
    LANGUAGES CXX
)

# --- Compiler settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# --- Output directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Find packages ---
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)

# --- Include directories ---
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

# --- Source groups for IDE navigation ---
file(GLOB_RECURSE RENDERER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/renderer/*.cpp
)
file(GLOB_RECURSE RENDERER_HEADERS
    ${CMAKE_SOURCE_DIR}/src/renderer/*.h
)
file(GLOB_RECURSE MATH_SOURCES
    ${CMAKE_SOURCE_DIR}/src/math/*.cpp
)
file(GLOB_RECURSE MATH_HEADERS
    ${CMAKE_SOURCE_DIR}/src/math/*.h
)
file(GLOB_RECURSE TESTS_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

# --- Main executable ---
add_executable(rengen
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${RENDERER_SOURCES}
    ${MATH_SOURCES}
)

target_link_libraries(rengen
    Threads::Threads
    PNG::PNG
)

# --- Tests executable ---
add_executable(rengen_tests
    ${CMAKE_SOURCE_DIR}/tests/external/catch_amalgamated.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
    ${TESTS_SOURCES}
    ${MATH_SOURCES}
    ${RENDERER_SOURCES}
)

target_link_libraries(rengen_tests
    Threads::Threads
    PNG::PNG
)

# --- Enable testing ---
enable_testing()
add_test(NAME rengen_tests COMMAND rengen_tests)

# --- Catch2 (single-header, vendored) ---
# We use the single-header Catch2 v3 from the tests/external directory.
# If not present, tests are still compiled but will fail to link until fetched.

cmake_minimum_required(VERSION 3.28)

project(mirage-math VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
endif()

set(SOURCES
    src/mirage-math.cpp
)

# set(HEADERS
#     include/your_header_file.h
# )

add_library(mirage-math ${SOURCES})
target_sources(mirage-math PUBLIC FILE_SET CXX_MODULES FILES ${SOURCES})

# target_include_directories(mirage-math PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# target_link_libraries(mirage-math)

set_target_properties(mirage-math PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# This file is a part of MRNIU/smcc
# (https://github.com/MRNIU/smcc).
#
# CMakeLists.txt for MRNIU/smcc.

add_library(${PROJECT_NAME} STATIC
        smcc.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-O3;-Werror>
        -Wall
        -Wextra
        -ffreestanding
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/smcc.h")

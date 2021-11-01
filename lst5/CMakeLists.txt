
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
project(lst5 C )

set(CMAKE_BINARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/bin/)


#
# Basic feature configuration
#
option(USE_GUI OFF)
option(USE_FFI ON)
option(USE_SOCKET ON)


if(USE_GUI)
    add_compile_options("-DLST_USE_SOCKET=1")
endif()

if(USE_FFI)
    add_compile_options("-DLST_USE_FFI=1")
endif()

if(USE_GUI)
    add_compile_options("-DLST_USE_GUI=1")
endif()

set(LST_SRC
        src/interp.c
        src/lst_primitives.c
        src/lst_ffi_primitives.c
        src/lst_socket_primitives.c
        src/memory.c
        src/main.c
)

add_executable(lst5 ${LST_SRC} )
target_include_directories(lst5 PUBLIC src)

add_executable(lst5-init imgbuild/imgbuilder.c)
target_include_directories(lst5-init PUBLIC imgbuild/)

cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(lst3 C )


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/)

set(LST_SRC
        src/memory.c
        src/names.c
        src/news.c
        src/interp.c
        src/primitive.c
        src/filein.c
        src/lex.c
        src/parser.c
        src/unixio.c
        src/tty.c
)

add_executable(lst3 ${LST_SRC}  st.c)
target_include_directories(lst3 PUBLIC inc/ inc/*)
target_link_libraries(lst3 -lm)

add_executable(lst3-init ${LST_SRC} src/initial.c)
target_include_directories(lst3-init PUBLIC inc/ inc/*)
target_link_libraries(lst3-init -lm)

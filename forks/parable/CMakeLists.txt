
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
project(parable C )

#set(CMAKE_BINARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/build/)

add_executable(parable 
		src/memory.c
		src/names.c
		src/news.c
		src/interp.c
		src/primitive.c
		src/filein.c
		src/lex.c
		src/parser.c
		src/unixio.c
		src/st.c
		src/tty.c
)

target_include_directories(parable PUBLIC src)
target_include_directories(parable PUBLIC imgbuild/)
target_link_libraries(parable m) # m for -lm

cmake_minimum_required(VERSION 3.12)
project(ft_ssl C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS} -g -DDEBUG")

add_subdirectory(libft)

add_executable(${PROJECT_NAME}
		source/md5/ft_md5.c
		source/md5/ft_md5_update_state.c
		source/sha256/ft_sha256.c
		source/sha256/ft_sha256_update_state.c
		source/ssl/ctx_data.c
		source/ssl/ssl.c
		source/ssl/ssl_parse.c
		source/ssl/ssl_print.c
		source/ssl/ssl_print_invalid.c
		source/ssl/ssl_run.c
		source/main.c)
target_link_libraries(${PROJECT_NAME} ft)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${ft_INCLUDES})

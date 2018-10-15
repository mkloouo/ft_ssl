cmake_minimum_required(VERSION 3.12)
project(ft_ssl C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS} -g -DDEBUG")

add_subdirectory(libft)
add_subdirectory(github-version)

add_executable(${PROJECT_NAME}
		source/main.c
		source/ssl/ft_sha256.c
		source/ssl/ft_md5.c)
target_link_libraries(${PROJECT_NAME} ft)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${ft_INCLUDES})

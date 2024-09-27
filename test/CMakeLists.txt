cmake_minimum_required(VERSION 3.29)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(publish_bin_debug ${PROJECT_SOURCE_DIR}/build/debug)
set(publish_bin_release ${PROJECT_SOURCE_DIR}/build/release)

# 指定可执行程序输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${publish_bin_debug})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${publish_bin_release})
file(COPY ${PROJECT_SOURCE_DIR}/Dependencies/freeglut.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
file(COPY ${PROJECT_SOURCE_DIR}/Dependencies/glew32.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
file(COPY ${PROJECT_SOURCE_DIR}/Dependencies/freeglut.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
file(COPY ${PROJECT_SOURCE_DIR}/Dependencies/glew32.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

add_executable(${PROJECT_NAME} main.cpp draw.h draw.cpp)

target_link_libraries(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/Dependencies/freeglut/freeglut.lib)
target_link_libraries(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/Dependencies/glew/glew32.lib)



cmake_minimum_required(VERSION 3.20)
project(Estudos_OpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(Triangulo
        Basico/Triangulos/main.cpp
        src/glad.c
)

add_executable(Quadrado
        Basico/Quadrado/main.cpp
        src/glad.c
)

target_link_libraries(Triangulo
        opengl32
        ${CMAKE_SOURCE_DIR}/libs/libglfw3.a
)

target_link_libraries(Quadrado
        opengl32
        ${CMAKE_SOURCE_DIR}/libs/libglfw3.a
)

add_custom_command(TARGET Triangulo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/glfw3.dll"
        $<TARGET_FILE_DIR:Triangulo>
)

add_custom_command(TARGET Quadrado POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/glfw3.dll"
        $<TARGET_FILE_DIR:Quadrado>
)

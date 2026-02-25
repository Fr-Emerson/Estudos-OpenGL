cmake_minimum_required(VERSION 3.20)
project(Estudos_OpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretório de headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# ================================
# Biblioteca comum (OpenGL base)
# ================================
add_library(OpenGLCommon
        src/glad.c
        src/shaderClass.cpp
        src/VAO.cpp
        src/VBO.cpp
        src/EBO.cpp
        src/stb_image.cpp
)

target_link_libraries(OpenGLCommon
        opengl32
        ${CMAKE_SOURCE_DIR}/libs/libglfw3.a
)


function(add_example NAME SOURCE)
    add_executable(${NAME} ${SOURCE})

    target_link_libraries(${NAME}
            OpenGLCommon
    )


    add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libs/glfw3.dll"
            $<TARGET_FILE_DIR:${NAME}>
    )
endfunction()

# ================================
# Exemplos
# ================================

add_example(Triangulo Basico/1-Triangulos/main.cpp)
add_example(Quadrado Basico/2-Quadrado/main.cpp)
add_example(VertexColor Basico/3-VertexColor/main.cpp)
add_example(Textura Basico/4-Textura/main.cpp)
add_example(Transform Basico/5-Transforms/main.cpp)
add_example(Coordenadas Basico/6-Coordenadas/main.cpp)
add_example(Camera Basico/7-Camera/main.cpp)
add_example(Cores Luz/1-CorLuz/main.cpp)
add_example(Fonte Luz/2-Fonte/main.cpp)


file(COPY src/Shaders/default.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/default.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/colors.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/colors.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/text.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/text.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/transform.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/transform.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/Coord.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/Coord.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/lightColor.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/lightColor.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/Shaders/LightSource.vert DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Shaders/LightSource.frag DESTINATION ${CMAKE_BINARY_DIR})

file(COPY src/gatito.jpg DESTINATION ${CMAKE_BINARY_DIR})

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Shader/shaderClass.h>
#include <VAO/VAO.h>
#include <VBO/VBO.h>
#include <EBO/EBO.h>
#include<iostream>
#include <stb_image/stb_image.h>
#include <glm/mat2x2.hpp>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Janela", nullptr, nullptr);
    if (window == NULL)
    {
        cout << "Erro ao criar janela" << endl;
        glfwTerminate();
        return -1 ;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Erro ao inicializar glad" << endl;
        return -1;
    }
    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shaderProgram("text.vert","text.frag");

    float vertices[] = {
        -0.5, 0.5f, 0.0f,       1.0f,0.0f,0.0f,     0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,       0.0f,1.0f,0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,     0.0f,0.0f,1.0f,     0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      1.0f,1.0f,0.0f,     1.0f, 0.0f
    };
    GLuint indices[] = {
        0,1,2,
        1,2,3
    };


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("gatito.jpg",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        cout << "Erro ao carregar a textura" << endl;
    }
    stbi_image_free(data);


    VAO vao;
    vao.Bind();
    VBO vbo(vertices,sizeof(vertices));
    EBO ebo(indices,sizeof(indices));
    vao.LinkVBO(vbo,0,3,8*(sizeof(float)),0);
    vao.LinkVBO(vbo,1,3,8*(sizeof(float)),3);
    vao.LinkVBO(vbo,2,2,8*(sizeof(float)),6);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();



    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();
        glBindTexture(GL_TEXTURE_2D,texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
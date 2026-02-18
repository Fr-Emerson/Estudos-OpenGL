#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Shader/shaderClass.h>
#include <VAO/VAO.h>
#include <VBO/VBO.h>
#include <EBO/EBO.h>
#include<iostream>
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

    Shader shaderProgram("colors.vert","colors.frag");
    float vertices[] = {
        //Posições             //Cores
        0.0, 0.5f, 0.0f,        1.0f,0.0f,0.0f,
        0.5f, -0.5f, 0.0f,      0.0f,1.0f,0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f,0.0f,1.0f,
    };
    VAO vao;
    vao.Bind();
    VBO vbo(vertices,sizeof(vertices));
    vao.LinkVBO(vbo,0,6*sizeof(float),0);
    vao.LinkVBO(vbo,1,6*sizeof(float),3);
    vao.Unbind();
    vbo.Unbind();



    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
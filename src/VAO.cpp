#include "../include/VAO/VAO.h"

VAO::VAO() {
    glGenVertexArrays(1,&ID);
}
/// <summary>
/// Vincula um VBO ao VAO atual, configurando como os dados de vértices
/// devem ser interpretados pela GPU.
/// </summary>
/// <param name="vbo">O VBO contendo os dados de vértices.</param>
/// <param name="layout">Índice do atributo de vértice no shader.</param>
/// <param name="stride">Espaçamento em bytes entre vértices consecutivos.</param>
/// <param name="offset">Deslocamento inicial do atributo, em número de floats.</param>
void VAO::LinkVBO(VBO vbo, GLuint layout,GLsizei stride ,int offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}
void VAO::Bind() {
    glBindVertexArray(ID);
}
void VAO::Unbind() {
    glBindVertexArray( 0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1,&ID);
}



#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <glad/glad.h>

#include "../EBO/EBO.h"
#include "../VBO/VBO.h"
class VAO {
public:
    GLuint ID;
    VAO ();
    void LinkVBO(VBO vbo, GLuint layout, GLsizei stride,int offset);
    void Bind();
    void Unbind();
    void Delete();
};
#endif //VAO_CLASS_H
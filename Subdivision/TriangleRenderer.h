#pragma once

#include "Renderer.h"


class TriangleRenderer : public Renderer {
public:
    TriangleRenderer();

    virtual void render() override;

    glm::vec3 eye;
    glm::mat4 view, perspective;
    GLuint VAO, VBO;
    Program program;
};


#pragma once

#include "Renderer.h"
#include <vector>
#include "Vertex.h"
#include "Mesh.h"


class TrunkRenderer : public Renderer {
public:
    TrunkRenderer();

    virtual void render() override;

    glm::vec3 eye;
    glm::mat4 view, perspective;
    GLuint VAO, VBO;
    Program program;
    std::vector<Vertex> vertices;
    Mesh mesh;

    bool subdividing;
};


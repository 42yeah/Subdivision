#pragma once

#include <glm/glm.hpp>


class Vertex {
public:
    Vertex() : position(0.0f), normal(0.0f), tex_coord(0.0f) {}

    Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 tex_coord) : position(p), normal(n), tex_coord(tex_coord) {
    }

    glm::vec3 position, normal;
    glm::vec2 tex_coord;
};

Vertex operator+(Vertex v1, Vertex v2);

Vertex operator*(const float scalar, Vertex v1);

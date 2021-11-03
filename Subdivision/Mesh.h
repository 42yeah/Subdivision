#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Vertex.h"


struct Edge {
    Vertex v1;
    Vertex v2;
};

struct Face {
    Edge e1;
    Edge e2;
    Edge e3;

    Vertex v1;
    Vertex v2;
    Vertex v3;
};

// Mesh grouped with faces & edges.
class Mesh {
public:
    Mesh() {
        init();
    }

    Mesh(std::string model_path, std::string mtl_search_path) {
        init(model_path, mtl_search_path);
    }

    void init();

    void init(std::string model_path, std::string mtl_search_path);

    std::vector<Vertex> to_vertices();

    void butterfly_subdivide();

    Vertex subdivide_edge(Face &f, Edge &e, Vertex &v);

    std::vector<Face> faces;
};


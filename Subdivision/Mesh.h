#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <optional>
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

    Face(Edge e1, Edge e2, Edge e3, Vertex v1, Vertex v2, Vertex v3);

    Face(Edge e1, Edge e2, Edge e3, Vertex v1, Vertex v2, Vertex v3, glm::vec3 eye_dir);
};

bool operator==(Edge a, Edge b);


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

    void butterfly_subdivide(glm::vec3 eye_dir);

    std::optional<Vertex> get_face_edge_adjacent_vertex(Face &f, Edge &e);

    Vertex subdivide_edge(Face &f, Edge &e, Vertex &b);

    std::vector<Face> faces;
};


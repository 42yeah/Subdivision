#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


bool operator==(Edge a, Edge b) {
    bool same_v1 = glm::distance(a.v1.position, b.v1.position) < 1e-2;
    bool same_v2 = glm::distance(a.v2.position, b.v2.position) < 1e-2;
    bool same_v1v2 = glm::distance(a.v2.position, b.v1.position) < 1e-2;
    bool same_v2v1 = glm::distance(a.v1.position, b.v2.position) < 1e-2;
    return (same_v1 && same_v2) || (same_v1v2 && same_v2v1);
}

Face::Face(Edge e1, Edge e2, Edge e3, Vertex v1, Vertex v2, Vertex v3) : e1(e1), e2(e2), e3(e3), v1(v1), v2(v2), v3(v3) {

}

Face::Face(Edge e1, Edge e2, Edge e3, Vertex v1, Vertex v2, Vertex v3, glm::vec3 eye_dir) : e1(e1), e2(e2), e3(e3), v1(v1), v2(v2), v3(v3) {
    // Update normals
    glm::vec3 dir1 = glm::normalize(v2.position - v1.position);
    glm::vec3 dir2 = glm::normalize(v3.position - v1.position);
    glm::vec3 norm = glm::cross(dir1, dir2);
    if (glm::dot(norm, eye_dir) > 0) {
        norm = -norm;
    }
    v1.normal = norm;
    v2.normal = norm;
    v3.normal = norm;
}

void Mesh::init() {
    faces.clear();

    Vertex v1({
        0.0f, 0.0f, 0.0f
    }, {
        0.0f, 0.0f, 1.0f
    }, {
        0.0f, 0.0f
    });

    Vertex v2({
     0.5f, 0.0f, 0.0f
    }, {
        0.0f, 0.0f, 1.0f
    }, {
        0.0f, 0.0f
    });

    Vertex v3({
        0.0f, 0.5f, 0.0f
    }, {
        0.0f, 0.0f, 1.0f
    }, {
        0.0f, 0.0f
    });

    Edge e1 = { v1, v2 };
    Edge e2 = { v2, v3 };
    Edge e3 = { v1, v3 };

    Face f(e1, e2, e3, v1, v2, v3);
    faces.push_back(f);
}

void Mesh::init(std::string model_path, std::string mtl_search_path) {
    faces.clear();

    tinyobj::ObjReaderConfig config;
    config.mtl_search_path = mtl_search_path;
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(model_path, config)) {
        std::cerr << "ERR! Failed to load the model." << std::endl;
        return;
    }
    if (!reader.Error().empty()) {
        std::cerr << "ERR! tinyobjloader failed with message: " << reader.Error() << std::endl;
        return;
    }
    if (!reader.Warning().empty()) {
        std::cout << "WARN! tinyobjloader succeeded with warning: " << reader.Warning() << std::endl;
    }
    auto& attribs = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // For each shape
    for (int i = 0; i < shapes.size(); i++) {
        tinyobj::mesh_t mesh = shapes[i].mesh;
        for (int j = 0; j < mesh.num_face_vertices.size(); j++) {
            // 's every triangle
            tinyobj::index_t idx1 = mesh.indices[j * 3 + 0];

            Vertex v1({
                attribs.vertices[idx1.vertex_index * 3 + 0],
                attribs.vertices[idx1.vertex_index * 3 + 1],
                attribs.vertices[idx1.vertex_index * 3 + 2]
            }, {
                attribs.normals[idx1.normal_index * 3 + 0],
                attribs.normals[idx1.normal_index * 3 + 1],
                attribs.normals[idx1.normal_index * 3 + 2],
            }, {
                0.0f, 0.0f
            });

            tinyobj::index_t idx2 = mesh.indices[j * 3 + 1];

            Vertex v2({
                attribs.vertices[idx2.vertex_index * 3 + 0],
                attribs.vertices[idx2.vertex_index * 3 + 1],
                attribs.vertices[idx2.vertex_index * 3 + 2]
            }, {
                attribs.normals[idx2.normal_index * 3 + 0],
                attribs.normals[idx2.normal_index * 3 + 1],
                attribs.normals[idx2.normal_index * 3 + 2],
            }, {
                0.0f, 0.0f
            });

            tinyobj::index_t idx3 = mesh.indices[j * 3 + 2];

            Vertex v3({
                attribs.vertices[idx3.vertex_index * 3 + 0],
                attribs.vertices[idx3.vertex_index * 3 + 1],
                attribs.vertices[idx3.vertex_index * 3 + 2]
            }, {
                attribs.normals[idx3.normal_index * 3 + 0],
                attribs.normals[idx3.normal_index * 3 + 1],
                attribs.normals[idx3.normal_index * 3 + 2],
            }, {
                0.0f, 0.0f
            });

            Edge e1 = { v1, v2 };
            Edge e2 = { v2, v3 };
            Edge e3 = { v1, v3 };

            Face f(e1, e2, e3, v1, v2, v3);
            faces.push_back(f);
        }
    }
}

std::vector<Vertex> Mesh::to_vertices() {
    std::vector<Vertex> vertices;

    for (int i = 0; i < faces.size(); i++) {
        vertices.push_back(faces[i].v1);
        vertices.push_back(faces[i].v2);
        vertices.push_back(faces[i].v3);
    }
    return vertices;
}

void Mesh::butterfly_subdivide(glm::vec3 eye_dir) {
    std::vector<Face> new_faces;
    for (int i = 0; i < faces.size(); i++) {
        Face &f = faces[i];

        Edge &e1 = f.e1;
        Edge &e2 = f.e2;
        Edge &e3 = f.e3;

        Vertex &v1 = f.v1;
        Vertex &v2 = f.v2;
        Vertex &v3 = f.v3;

        Vertex v4 = subdivide_edge(f, e1, v3);
        Vertex v5 = subdivide_edge(f, e2, v1);
        Vertex v6 = subdivide_edge(f, e3, v2);

        Face f1(Edge{ v1, v4 }, Edge{ v4, v6 }, Edge{ v1, v6 }, v1, v4, v6);
        Face f2(Edge{ v4, v2 }, Edge{ v2, v5 }, Edge{ v4, v5 }, v4, v2, v5);
        Face f3(Edge{ v6, v5 }, Edge{ v5, v3 }, Edge{ v6, v3 }, v6, v5, v3);
        Face f4(Edge{ v4, v5 }, Edge{ v5, v6 }, Edge{ v4, v6 }, v4, v5, v6);
        
        new_faces.push_back(f1);
        new_faces.push_back(f2);
        new_faces.push_back(f3);
        new_faces.push_back(f4);
    }
    faces = new_faces;
}

std::optional<Vertex> Mesh::get_face_edge_adjacent_vertex(Face& f1, Edge& e) {
    for (int i = 0; i < faces.size(); i++) {
        if (&faces[i] == &f1) {
            continue;
        }
        Face &f2 = faces[i];
        if (f2.e1 == e) {
            return f2.v3;
        }
        if (f2.e2 == e) {
            return f2.v1;
        }
        if (f2.e3 == e) {
            return f2.v2;
        }
    }
    return {};
}

Vertex Mesh::subdivide_edge(Face& f, Edge& e, Vertex& b) {
    Vertex ret = 0.5f * (e.v1 + e.v2);
    // Now for b
    auto b2 = get_face_edge_adjacent_vertex(f, e);
    if (b2.has_value()) {
        ret = ret + 0.125f * b + 0.125f * *b2;
    }
    return ret;
}


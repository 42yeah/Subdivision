#include "Vertex.h"


Vertex operator+(Vertex v1, Vertex v2) {
    v1.position += v2.position;
    v1.normal += v2.normal;
    return v1;
}

Vertex operator*(const float scalar, Vertex v1) {
    v1.position *= scalar;
    v1.normal *= scalar;
    return v1;
}

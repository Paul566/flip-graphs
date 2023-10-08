#include "Triangle.h"


Triangle::Triangle(Point v1, Point v2, Point v3) {
    this->vertices = std::vector<Point>({v1, v2, v3});
}

int Triangle::NumberCommonVertices(const Triangle& triangle_a, const Triangle& triangle_b) {
    int num_common_vertices = 0;
    for (const auto& vertex_a : triangle_a.vertices) {
        for (const auto& vertex_b : triangle_b.vertices) {
            if (vertex_a == vertex_b)
                num_common_vertices++;
        }
    }

    return num_common_vertices;
}

bool Triangle::CanBeFlipped(Triangle& triangle_a, Triangle& triangle_b) {
    if (NumberCommonVertices(triangle_a, triangle_b) != 2)
        return false;

    Point a, b, c, d;    // a, b are the common vertices, c is from triangle_a, d is from triangle_b

    bool a_taken = false;
    for (const auto& vertex_a : triangle_a.vertices) {
        for (const auto& vertex_b : triangle_b.vertices) {
            if (vertex_a == vertex_b) {
                if (not a_taken) {
                    a = Point(vertex_a);
                    a_taken = true;
                } else {
                    b = Point(vertex_a);
                }
            }
        }
    }
    for (auto& vertex_a : triangle_a.vertices) {
        if ((a != vertex_a) && (vertex_a != b))
            c = vertex_a;
    }
    for (const auto& vertex_b : triangle_b.vertices) {
        if ((vertex_b != a) && (vertex_b != b))
            d = vertex_b;
    }

    // check if c and d are on the opposite sides of line ab
    if (((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) *
            ((b.x - a.x) * (d.y - a.y) - (d.x - a.x) * (b.y - a.y)) > 0)
        return false;

    // check if a and b are on the opposite sides of line cd
    if (((d.x - c.x) * (b.y - c.y) - (b.x - c.x) * (d.y - c.y)) *
        ((d.x - c.x) * (a.y - c.y) - (a.x - c.x) * (d.y - c.y)) > 0)
        return false;

    return true;
}

bool Triangle::operator==(const Triangle& other) const {
    return NumberCommonVertices(*this, other) == 3;
}

bool Triangle::operator!=(const Triangle &other) const {
    return !(*this == other);
}

size_t HashTriangle::operator()(const Triangle& triangle) const {
    return HashPoint{}(triangle.vertices[0]) ^
            HashPoint{}(triangle.vertices[1]) ^
            HashPoint{}(triangle.vertices[2]);
}

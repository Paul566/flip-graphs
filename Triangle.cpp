#include <cmath>
#include <iostream>
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

bool Triangle::CanBeFlipped(const Triangle& triangle_a, const Triangle& triangle_b) {
    if (NumberCommonVertices(triangle_a, triangle_b) != 2)
        return false;

    Point a, b, c, d;    // a, b are the common vertices, c is from triangle_a, d is from triangle_b

    bool a_taken = false;
    for (const auto& vertex_a : triangle_a.vertices) {
        for (const auto& vertex_b : triangle_b.vertices) {
            if (vertex_a == vertex_b) {
                if (not a_taken) {
                    a = Point(vertex_a.x, vertex_a.y);
                    a_taken = true;
                } else {
                    b = Point(vertex_a.x, vertex_a.y);
                }
            }
        }
    }
    for (auto& vertex_a : triangle_a.vertices) {
        if ((a != vertex_a) && (b != vertex_a))
            c = Point(vertex_a.x, vertex_a.y);
    }
    for (const auto& vertex_b : triangle_b.vertices) {
        if ((vertex_b != a) && (b != vertex_b))
            d = Point(vertex_b.x, vertex_b.y);
    }

    if ((std::abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) < 1e-6) ||
            (std::abs((b.x - a.x) * (d.y - a.y) - (d.x - a.x) * (b.y - a.y)) < 1e-6) ||
            (std::abs((d.x - c.x) * (b.y - c.y) - (b.x - c.x) * (d.y - c.y)) < 1e-6) ||
            (std::abs((d.x - c.x) * (a.y - c.y) - (a.x - c.x) * (d.y - c.y)) < 1e-6)) {
        throw std::runtime_error("zero det");
    }

    // check if c and d are on the opposite sides of line ab
    if ((((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) > 0) ==
        (((b.x - a.x) * (d.y - a.y) - (d.x - a.x) * (b.y - a.y)) > 0))
        return false;

    // check if a and b are on the opposite sides of line cd
    if ((((d.x - c.x) * (b.y - c.y) - (b.x - c.x) * (d.y - c.y)) > 0) ==
        (((d.x - c.x) * (a.y - c.y) - (a.x - c.x) * (d.y - c.y)) > 0))
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
    return std::hash<double>{}(std::round(
                triangle.vertices[0].x * triangle.vertices[1].x * triangle.vertices[2].x * 1e3+
                triangle.vertices[0].y * triangle.vertices[1].y * triangle.vertices[2].y * 1e3
            ));
}

#include "Triangle.h"


Triangle::Triangle(Point v1, Point v2, Point v3) {
    this->vertices = std::vector<std::shared_ptr<Point>>({
        std::make_shared<Point>(v1), std::make_shared<Point>(v2), std::make_shared<Point>(v3)});
}

int Triangle::NumberCommonVertices(const std::shared_ptr<Triangle>& triangle_a,
                                   const std::shared_ptr<Triangle>& triangle_b) {
    int num_common_vertices = 0;
    for (const auto& vertex_a : triangle_a->vertices) {
        for (const auto& vertex_b : triangle_b->vertices) {
            if (vertex_a == vertex_b)
                num_common_vertices++;
        }
    }

    return num_common_vertices;
}

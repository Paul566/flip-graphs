#include "Triangulation.h"

#include <utility>

Triangulation::Triangulation(std::unordered_set<Triangle, HashTriangle> &triangles_) {
    this->triangles = std::move(triangles_);
}

std::vector<Triangulation> Triangulation::GetChildren() {
    std::vector<Triangulation> children;

    for (auto triangle_a_ptr = (this->triangles).begin(); triangle_a_ptr != (this->triangles).end(); ++triangle_a_ptr) {
        for (auto triangle_b_ptr = triangle_a_ptr; triangle_b_ptr != (this->triangles).end(); ++triangle_b_ptr) {
            if (Triangle::CanBeFlipped(*triangle_a_ptr, *triangle_b_ptr)) {
                // TODO remove this copy-paste
                Point a, b, c, d;    // a, b are the common vertices, c is from triangle_a, d is from triangle_b

                bool a_taken = false;
                for (const auto& vertex_a : triangle_a_ptr->vertices) {
                    for (const auto& vertex_b : triangle_b_ptr->vertices) {
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
                for (auto& vertex_a : triangle_a_ptr->vertices) {
                    if ((a != vertex_a) && (b != vertex_a))
                        c = Point(vertex_a.x, vertex_a.y);
                }
                for (const auto& vertex_b : triangle_b_ptr->vertices) {
                    if ((vertex_b != a) && (b != vertex_b))
                        d = Point(vertex_b.x, vertex_b.y);
                }

                Triangle new_triangle_1 = Triangle(a, c, d);
                Triangle new_triangle_2 = Triangle(b, c, d);

                std::unordered_set<Triangle, HashTriangle> new_triangles;
                new_triangles.insert(new_triangle_1);
                new_triangles.insert(new_triangle_2);
                for (const auto& triangle : this->triangles) {
                    if ((triangle != *triangle_a_ptr) && (triangle != *triangle_b_ptr)) {
                        new_triangles.insert(triangle);
                    }
                }

                Triangulation new_triangulation = Triangulation(new_triangles);
                // TODO optimize this
                children.push_back(new_triangulation);
            }
        }
    }

    return children;
}

bool Triangulation::operator==(const Triangulation& other) const {
    return this->triangles == other.triangles;
}

size_t HashTriangulation::operator()(const Triangulation &triangulation) const {
    size_t hash = 0;
    for (const auto& triangle : triangulation.triangles) {
        hash ^= HashTriangle{}(triangle);
    }
    return hash;
}

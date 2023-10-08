#include "Triangulation.h"

#include <utility>


Triangulation::Triangulation(std::unordered_set<Triangle, HashTriangle> &triangles_,
                             std::vector<std::pair<Triangle, Triangle>> &bordering_triangles_) {
    this->triangles = triangles_;
    this->bordering_triangles = bordering_triangles_;
}

Triangulation::Triangulation(std::unordered_set<Triangle, HashTriangle> &triangles_) {
    this->triangles = std::move(triangles_);
    this->bordering_triangles = std::vector<std::pair<Triangle, Triangle>>();

    for (auto triangle_a_ptr = (this->triangles).begin(); triangle_a_ptr != (this->triangles).end(); ++triangle_a_ptr) {
        for (auto triangle_b_ptr = triangle_a_ptr; triangle_b_ptr != (this->triangles).end(); ++triangle_b_ptr) {
            if (Triangle::NumberCommonVertices(*triangle_a_ptr, *triangle_b_ptr) == 2)
                bordering_triangles.emplace_back(*triangle_a_ptr, *triangle_b_ptr);
        }
    }
}

std::vector<Triangulation> Triangulation::GetChildren() {
    std::vector<Triangulation> children;

    for (auto& two_triangles : this->bordering_triangles) {
        if (Triangle::CanBeFlipped(two_triangles.first, two_triangles.second)) {
            // TODO remove this copy-paste
            Point a, b, c, d;    // a, b are the common vertices, c is from triangle_a, d is from triangle_b

            bool a_taken = false;
            for (const auto& vertex_a : two_triangles.first.vertices) {
                for (const auto& vertex_b : two_triangles.second.vertices) {
                    if (vertex_a == vertex_b) {
                        if (not a_taken) {
                            a = vertex_a;
                            a_taken = true;
                        } else {
                            b = vertex_a;
                        }
                    }
                }
            }
            for (const auto& vertex_a : two_triangles.first.vertices) {
                if ((vertex_a != a) && (vertex_a != b))
                    c = vertex_a;
            }
            for (const auto& vertex_b : two_triangles.second.vertices) {
                if ((vertex_b != a) && (vertex_b != b))
                    d = vertex_b;
            }

            Triangle new_triangle_1 = Triangle(a, c, d);
            Triangle new_triangle_2 = Triangle(b, c, d);

            std::unordered_set<Triangle, HashTriangle> new_triangles;
            new_triangles.insert(new_triangle_1);
            new_triangles.insert(new_triangle_2);
            for (const auto& triangle : this->triangles) {
                if ((triangle != two_triangles.first) && (triangle != two_triangles.second)) {
                    new_triangles.insert(triangle);
                }
            }

            Triangulation new_triangulation = Triangulation(new_triangles);
            // TODO optimize this, calculate new bordering triangles faster
            children.push_back(new_triangulation);
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

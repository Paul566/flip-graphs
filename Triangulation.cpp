#include "Triangulation.h"

#include <utility>

Triangulation::Triangulation(std::vector<std::shared_ptr<Triangle>> triangles_,
                             std::vector<std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>>> bordering_triangles_) {
    this->triangles = std::move(triangles_);
    this->bordering_triangles = std::move(bordering_triangles_);
}

Triangulation::Triangulation(std::vector<std::shared_ptr<Triangle>> triangles_) {
    this->triangles = std::move(triangles_);
    this->bordering_triangles = std::vector<std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>>>();

    for (const auto& triangle_a : this->triangles) {
        for (const auto& triangle_b : this->triangles) {
            if (Triangle::NumberCommonVertices(triangle_a, triangle_b) == 2)
                bordering_triangles.emplace_back(triangle_a, triangle_b);
        }
    }
}

#ifndef FLIP_GRAPHS_TRIANGULATION_H
#define FLIP_GRAPHS_TRIANGULATION_H

#include <vector>
#include <unordered_set>

#include "Triangle.h"

class Triangulation {
    std::unordered_set<std::shared_ptr<Triangle>> triangles;
    std::vector<std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>>> bordering_triangles;

    Triangulation(std::unordered_set<std::shared_ptr<Triangle>> triangles_,
                  std::vector<std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>>> bordering_triangles_);

    explicit Triangulation(std::unordered_set<std::shared_ptr<Triangle>> triangles_);

    std::vector<Triangulation> GetChildren();
};


#endif

#ifndef FLIP_GRAPHS_TRIANGULATION_H
#define FLIP_GRAPHS_TRIANGULATION_H

#include <vector>
#include <unordered_set>

#include "Triangle.h"

class Triangulation {
public:
    std::unordered_set<Triangle, HashTriangle> triangles;

    std::vector<Triangulation> GetChildren();

    explicit Triangulation(std::unordered_set<Triangle, HashTriangle> &triangles_);

    bool operator==(const Triangulation& other) const;
};

class HashTriangulation {
public:
    size_t operator()(const Triangulation &triangulation) const;
};

#endif

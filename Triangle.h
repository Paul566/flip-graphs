#ifndef FLIP_GRAPHS_TRIANGLE_H
#define FLIP_GRAPHS_TRIANGLE_H

#include <vector>
#include <memory>

#include "Point.h"


class Triangle {
public:
    std::vector<Point> vertices;

    Triangle(Point v1, Point v2, Point v3);

    static int NumberCommonVertices(const Triangle& triangle_a, const Triangle& triangle_b);

    static bool CanBeFlipped(Triangle& triangle_a, Triangle& triangle_b);

    bool operator==(const Triangle& other) const;

    bool operator!=(const Triangle& other) const;
};

class HashTriangle {
public:
    size_t operator()(const Triangle& triangle) const;
};


#endif

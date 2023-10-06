#ifndef FLIP_GRAPHS_TRIANGLE_H
#define FLIP_GRAPHS_TRIANGLE_H

#include <vector>
#include <memory>

#include "Point.h"


class Triangle {
public:
    std::vector<std::shared_ptr<Point>> vertices;

    Triangle(Point v1, Point v2, Point v3);

    static int NumberCommonVertices(const std::shared_ptr<Triangle>& triangle_a,
                                    const std::shared_ptr<Triangle>& triangle_b);
};


#endif

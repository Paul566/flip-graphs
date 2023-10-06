#ifndef FLIP_GRAPHS_TRIANGLE_H
#define FLIP_GRAPHS_TRIANGLE_H

#include <vector>
#include <memory>

#include "Point.h"


class Triangle {
public:
    std::vector<std::shared_ptr<Point>> vertices;

    Triangle(std::shared_ptr<Point> v1, std::shared_ptr<Point> v2, std::shared_ptr<Point> v3);

    static int NumberCommonVertices(const std::shared_ptr<Triangle>& triangle_a,
                                    const std::shared_ptr<Triangle>& triangle_b);

    static bool CanBeFlipped(const std::shared_ptr<Triangle>& triangle_a, const std::shared_ptr<Triangle>& triangle_b)
};


#endif

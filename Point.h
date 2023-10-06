#ifndef FLIP_GRAPHS_POINT_H
#define FLIP_GRAPHS_POINT_H


#include <memory>

class Point {
private:
    double tolerance = 1e-6;

public:
    double x, y;

    Point(double x_, double y_);
    Point();
    explicit Point(const std::shared_ptr<Point>& point_pointer);

    bool operator==(Point other) const;
};


#endif

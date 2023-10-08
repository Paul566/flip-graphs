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

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;
};

class HashPoint {
public:
    size_t operator()(const Point &point) const;
};


#endif

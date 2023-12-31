#ifndef FLIP_GRAPHS_POINT_H
#define FLIP_GRAPHS_POINT_H


#include <memory>

class Point {
private:
    float tolerance = 1e-3;

public:
    float x, y;

    Point(float x_, float y_);

    Point();

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;
};

#endif

#ifndef FLIP_GRAPHS_POINT_H
#define FLIP_GRAPHS_POINT_H


class Point {
private:
    double tolerance = 1e-6;

public:
    double x, y;

    Point(double x_, double y_);

    bool operator==(Point other) const;
};


#endif

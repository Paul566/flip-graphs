#include <cmath>
#include "Point.h"

Point::Point(double x_, double y_) {
    this->x = x_;
    this->y = y_;
}

Point::Point() {
    this->x = 0.;
    this->y = 0.;
}

bool Point::operator==(const Point &other) const {
    if (this->x > other.x + this->tolerance)
        return false;
    if (this->x < other.x - this->tolerance)
        return false;
    if (this->y > other.y + this->tolerance)
        return false;
    if (this->y < other.y - this->tolerance)
        return false;

    return true;
}

bool Point::operator!=(const Point &other) const {
    return !(*this == other);
}

size_t HashPoint::operator()(const Point &point) const {
    return std::hash<double>{}(std::round(point.x * 1e6)) ^ std::hash<double>{}(std::round(point.y * 1e6));
}

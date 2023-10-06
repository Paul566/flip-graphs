#include "Point.h"

Point::Point(double x_, double y_) {
    this->x = x_;
    this->y = y_;
}

bool Point::operator==(Point other) const {
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

#include "Point.h"

Point::Point(double x_, double y_) {
    this->x = x_;
    this->y = y_;
}

Point::Point() {
    this->x = 0.;
    this->y = 0.;
}

Point::Point(const std::shared_ptr<Point>& point_pointer) {
    this->x = point_pointer->x;
    this->y = point_pointer->y;
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

#include "point.h"

Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

std::ostream & operator<<( std::ostream & out, const Point & point ) {
    out << "(" << point.getX() << "," << point.getY() << ")";
    return out;
}

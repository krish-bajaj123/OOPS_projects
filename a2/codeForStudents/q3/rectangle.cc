#include "rectangle.h"

Rectangle::Rectangle(Point upperLeft, int height, int width, Colour colour)
    : point(upperLeft), height(height), width(width), colour(colour) {}

void Rectangle::translate(int x, int y) {
    point = Point(point.getX() + x, point.getY() + y);
}

void Rectangle::scale(float heightFactor, float widthFactor) {
    height *= heightFactor;
    width *= widthFactor;
}

void Rectangle::change(Colour newColour) {
    colour = newColour;
}

Colour Rectangle::getColour() const {
    return colour;
}

Point Rectangle::getPoint() const {
    return point;
}

int Rectangle::getWidth() const {
    return width;
}

int Rectangle::getHeight() const {
    return height;
}

std::istream& operator>>(std::istream& in, Rectangle& rectangle) {
    char colourChar;
    int x, y, h, w;
    in >> colourChar >> x >> y >> h >> w;
    Colour colour = translateColour(colourChar);
    rectangle = Rectangle(Point(x, y), h, w, colour);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rectangle& rectangle) {
    out << "[";
    switch(rectangle.getColour()) {
        case Colour::Red:
            out << "Red";
            break;
        case Colour::Green:
            out << "Green";
            break;
        case Colour::Blue:
            out << "Blue";
            break;
        case Colour::Orange:
            out << "Orange";
            break;
        case Colour::Yellow:
            out << "Yellow";
            break;
        case Colour::Black:
            out << "Black";
            break;
        case Colour::White:
            out << "White";
            break;
    }
    out << " (" << rectangle.getPoint().getX() << "," << rectangle.getPoint().getY() << ") "
        << rectangle.getHeight() << "x" << rectangle.getWidth() << "]";
    return out;
}

Colour translateColour( char c ) {
    switch( c ) {
        case 'r' : return Colour::Red;
        case 'g' : return Colour::Green;
        case 'b' : return Colour::Blue;
        case 'y' : return Colour::Yellow;
        case 'o' : return Colour::Orange;
        case 'a' : return Colour::Black;
        case 'w' : return Colour::White;
    }
    return Colour::Red;
} // translate

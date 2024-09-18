#include "canvas.h"
#include <algorithm> // For std::copy
#include <utility>   // For std::swap

Canvas::Canvas() : height(0), width(0) {}

// Copy constructor
Canvas::Canvas(const Canvas &other) {
    // Initialize fields
    height = other.height;
    width = other.width;
    // Deep copy rectangles
    for (const auto &rect : other.rectangles) {
        rectangles.push_back(rect);
    }
}

// Move constructor
Canvas::Canvas(Canvas &&other) {
    // Move height and width
    height = other.height;
    width = other.width;
    // Move rectangles
    rectangles = std::move(other.rectangles);
    // Reset other's height and width
    other.height = 0;
    other.width = 0;
}

// Destructor
Canvas::~Canvas() {
    // No need to explicitly deallocate memory, as rectangles vector handles it
}

// Copy assignment operator
Canvas &Canvas::operator=(const Canvas &other) {
    if (this != &other) {
        // Copy height and width
        height = other.height;
        width = other.width;
        // Deep copy rectangles
        rectangles.clear();
        for (const auto &rect : other.rectangles) {
            rectangles.push_back(rect);
        }
    }
    return *this;
}

// Move assignment operator
Canvas &Canvas::operator=(Canvas &&other) {
    if (this != &other) {
        // Move height and width
        height = other.height;
        width = other.width;
        // Move rectangles
        rectangles = std::move(other.rectangles);
        // Reset other's height and width
        other.height = 0;
        other.width = 0;
    }
    return *this;
}

// Removes all rectangles from the canvas.
void Canvas::empty() {
    rectangles.clear();
    height = 0;
    width = 0;
}

// Adds the given Rectangle after already existing rectangles.
void Canvas::add(const Rectangle &rectangle) {
    // Update height and width if necessary
    int rectHeight = rectangle.getHeight() + rectangle.getPoint().getY();
    int rectWidth = rectangle.getWidth() + rectangle.getPoint().getX();
    height = std::max(height, rectHeight);
    width = std::max(width, rectWidth);
    // Add rectangle
    rectangles.push_back(rectangle);
}

// Returns the number of rectangles in the Canvas.
int Canvas::numRectangles() const {
    return rectangles.size();
}

// Returns the width of the Canvas.
int Canvas::getWidth() const {
    return width;
}

// Returns the height of the Canvas.
int Canvas::getHeight() const {
    return height;
}

// Returns the Rectangle at the specified index.
Rectangle Canvas::get(int rectangleId) const {
    if (rectangleId >= 0 && rectangleId < rectangles.size()) {
        return rectangles[rectangleId];
    }
    // Return a default Rectangle if index is out of range
    return Rectangle();
}

// Translates the Rectangle at the specified index by the given offsets.
void Canvas::translate(int rectangleId, int x, int y) {
    if (rectangleId >= 0 && rectangleId < rectangles.size()) {
        rectangles[rectangleId].translate(x, y);
    }
}

// Scales the Rectangle at the specified index by the given factors.
void Canvas::scale(int rectangleId, float heightFactor, float widthFactor) {
    if (rectangleId >= 0 && rectangleId < rectangles.size()) {
        rectangles[rectangleId].scale(heightFactor, widthFactor);
    }
}

// Changes the colour of the Rectangle at the specified index.
void Canvas::change(int rectangleId, Colour newColour) {
    if (rectangleId >= 0 && rectangleId < rectangles.size()) {
        rectangles[rectangleId].change(newColour);
    }
}

// Removes the Rectangle at the specified index.
void Canvas::remove(int rectangleId) {
    if (rectangleId >= 0 && rectangleId < rectangles.size()) {
        rectangles.erase(rectangles.begin() + rectangleId);
    }
}

// Overloaded output operator to print the Canvas.
std::ostream &operator<<(std::ostream &out, const Canvas &canvas) {
    out << "Dimensions: " << canvas.getHeight() << "x" << canvas.getWidth() << std::endl;
    out << "Number of rectangles: " << canvas.numRectangles() << std::endl;
    for (const auto &rect : canvas.rectangles) {
        out << '\t' << rect << std::endl;
    }
    return out;
}
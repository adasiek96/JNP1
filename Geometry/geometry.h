#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <typeinfo>
#include <vector>
#include <cstddef>
#include <utility>

using namespace std;

class Position;
class Vector;
class Rectangle;
class Rectangles;

class Position {
public:
    // Creates and returns an object Position(x, y).
    Position(int32_t x, int32_t y) : _x(x), _y(y) {}

    // Implements operator which compares positions.
    bool operator==(const Position& rhs) const;

    // Returns the first coordinate.
    int32_t x() const { return _x; }

    // Returns the second coordinate.
    int32_t y() const { return _y; }

    // Returns a diverted position (in which x = y and y = x).
    Position reflection() const { return Position(this->y(), this->x()); }

    // Implements operator which adds a vector to the position.
    Position& operator+=(const Vector& rhs);

    // Returns unmodifiable object Position(0, 0).
    static const Position origin() { return Position(0, 0); }

private:
    // Position coordinates.
    int32_t _x, _y;
};

class Vector {
public:
    // Creates and returns an object Vector(x, y).
    Vector(int32_t x, int32_t y) : _x(x), _y(y) {}

    // Implements operator which compares vectors.
    bool operator==(const Vector& rhs) const;

    // Returns the first coordinate.
    int32_t x() const { return _x; }

    // Returns the second coordinate.
    int32_t y() const { return _y; }

    // Returns a diverted vector (in which x = y and y = x).
    Vector reflection() const { return Vector(this->y(), this->x()); }

    // Implements operator which adds a vector to the vector.
    Vector& operator+=(const Vector& rhs);

private:
    // Vector coordinates.
    int32_t _x, _y;
};

class Rectangle {
public:
    // Creates and returns an object Rectangle(width, height, position),
    // where a position is the position of the left corner of the rectangle.
    Rectangle(int32_t width, int32_t height, const Position& position);

    // Creates and returns an object Rectangle(width, height, Position(0, 0)).
    Rectangle(int32_t width, int32_t height);

    // Implements operator which compares rectangles.
    bool operator==(const Rectangle& rhs) const;

    // Returns the width.
    int32_t width() const { return _width; }

    // Returns the height.
    int32_t height() const { return _height; }

    // Returns the position of the left corner.
    const Position& pos() const { return _pos; }

    // Returns a diverted rectangle (in which x = y and y = x).
    Rectangle reflection() const;

    // Implements operator which adds a vector to the rectangle.
    Rectangle& operator+=(const Vector& rhs);

    // Returns the area of the rectangle.
    int32_t area() const { return width() * height(); }

    // Returns a pair of new rectangles in which the rectangles arise from the
    // old rectangle by splitting this rectangle along the X axis.
    pair<Rectangle, Rectangle> split_horizontally(int32_t place) const;

    // Runs analogously to the previous method.
    pair<Rectangle, Rectangle> split_vertically(int32_t place) const;

private:
    // Width and height of the rectangle.
    int32_t _width, _height;
    // Position of the left corner of the rectangle.
    Position _pos;
};

class Rectangles {
public:
    // Creates and returns an empty collection of rectangles.
    Rectangles() = default;
    
    // Creates and returns a collection of rectangles from the list by copying.
    Rectangles(const initializer_list<Rectangle>& l) : _rectangles(l) {}

    // Creates and returns a collection of rectangles from the list by moving.
    Rectangles(initializer_list<Rectangle>&& l) : _rectangles(move(l)) {}

    // Returns the number of rectangles.
    size_t size() const { return _rectangles.size(); }

    // Implement operator which gives a referance to the i-th rectangle.
    Rectangle& operator[](size_t i);
    const Rectangle& operator[](size_t i) const;

    // Implements operator which compares the collection of rectangles.
    bool operator==(const Rectangles& rhs) const;

    // Implement operator which adds a vector to every rectangle from the
    // collection.
    Rectangles& operator+=(const Vector& rhs);

    // Inserts a two new rectangles, which arise from the idx-th rectangle by
    // splitting this rectangle along the X axis, to the place of the idx-th
    // rectangle.
    void split_horizontally(int idx, int32_t place);

    // Runs analogously to the previous method.
    void split_vertically(int idx, int32_t place);

private:
    // Collection of rectangles.
    vector<Rectangle> _rectangles;

    // Returns the collection of rectangles.
    const vector<Rectangle>& rectangles() const { return _rectangles; }
};

// Implement operator which adds position and vector.
const Position operator+(const Position& p, const Vector& v);

const Position operator+(const Vector& v, const Position& p);

// Implements operator which adds two vectors.
const Vector operator+(const Vector& v1, const Vector& v2);

// Implement operator which adds rectangle and vector.
const Rectangle operator+(const Rectangle& r, const Vector& v);

const Rectangle operator+(const Vector& v, const Rectangle& r);

// Implement operator which adds vector to every rectangle from collections
// of rectangles by copying rectangles.
const Rectangles operator+(const Rectangles& r, const Vector& v);

const Rectangles operator+(const Vector& v, const Rectangles& r);

// Implement operator which adds vector to every rectangle from collections
// of rectangles by moving rectangles.
const Rectangles operator+(Rectangles&& r, const Vector& v);

const Rectangles operator+(const Vector& v, Rectangles&& r);

// Merge two rectangles along X axis and Y axis respectively and return a new
// rectangle.
Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

#endif

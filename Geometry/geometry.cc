#include <iostream>
#include <typeinfo>
#include <cassert>
#include "geometry.h"

using namespace std;


bool Position::operator==(const Position& rhs) const {
    return this->_x == rhs.x() && this->_y == rhs.y();
}

Position& Position::operator+=(const Vector& rhs) {
    this->_x += rhs.x();
    this->_y += rhs.y();
    return *this;
}


bool Vector::operator==(const Vector& rhs) const {
    return this->x() == rhs.x() && this->y() == rhs.y();
}

Vector& Vector::operator+=(const Vector& rhs) {
    this->_x += rhs.x();
    this->_y += rhs.y();
    return *this;
}


Rectangle::Rectangle(int32_t width, int32_t height, const Position& position)
        : _width(width), _height(height), _pos(position) {
    assert(width > 0 && height > 0);
}

Rectangle::Rectangle(int32_t width, int32_t height)
        : _width(width), _height(height), _pos(0, 0) {
    assert(width > 0 && height > 0);
}

bool Rectangle::operator==(const Rectangle& rhs) const {
    return this->width() == rhs.width()
           && this->height() == rhs.height()
           && this->pos() == rhs.pos();
}

Rectangle Rectangle::reflection() const {
    return Rectangle(this->height(), this->width(), this->pos().reflection());
}

Rectangle& Rectangle::operator+=(const Vector& rhs) {
    this->_pos += rhs;
    return *this;
}

pair<Rectangle, Rectangle> Rectangle::split_horizontally(int32_t place) const {
    assert(place <= this->height() && place > 0);
    return pair<Rectangle, Rectangle>(
            Rectangle(this->width(), place, this->pos()),
            Rectangle(this->width(), this->height() - place,
                      Position(this->pos().x(), this->pos().y() + place)));
}

pair<Rectangle, Rectangle> Rectangle::split_vertically(int32_t place) const {
    assert(place <= this->width() && place > 0);
    return std::pair<Rectangle, Rectangle>(
            Rectangle(place, this->height(), this->pos()),
            Rectangle(this->width() - place, this->height(),
                      Position(this->pos().x() + place, this->pos().y())));
}


Rectangle& Rectangles::operator[](size_t i) {
    assert(i < this->size());
    return this->_rectangles[i];
}

const Rectangle& Rectangles::operator[](size_t i) const {
    assert(i < this->size());
    return this->_rectangles[i];
}

bool Rectangles::operator==(const Rectangles& rhs) const {
    if (this->size() != rhs.size()) {
        return false;
    }
    return equal(this->_rectangles.begin(), this->_rectangles.end(),
                      rhs.rectangles().begin());
}

Rectangles& Rectangles::operator+=(const Vector& rhs) {
    for (auto& rect : this->_rectangles) {
        rect += rhs;
    }
    return *this;
}

void Rectangles::split_horizontally(int idx, int32_t place) {
    assert((size_t)idx < this->size() && place > 0);
    auto it = this->_rectangles.begin() + idx;
    auto splitted = it->split_horizontally(place);
    *it = splitted.first;
    this->_rectangles.insert(it + 1, splitted.second);
}

void Rectangles::split_vertically(int idx, int32_t place) {
    assert((size_t)idx < this->size() && place > 0);
    auto it = this->_rectangles.begin() + idx;
    auto splitted = it->split_vertically(place);
    *it = splitted.first;
    this->_rectangles.insert(it + 1, splitted.second);
}


const Position operator+(const Position& p, const Vector& v) {
    return Position(p) += v;
}

const Position operator+(const Vector& v, const Position& p) {
    return Position(p) += v;
}

const Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1) += v2;
}

const Rectangle operator+(const Rectangle& r, const Vector& v) {
    return Rectangle(r) += v;
}

const Rectangle operator+(const Vector& v, const Rectangle& r) {
    return Rectangle(r) += v;
}

const Rectangles operator+(const Rectangles& r, const Vector& v) {
    return Rectangles(r) += v;
}

const Rectangles operator+(const Vector& v, const Rectangles& r) {
    return Rectangles(r) += v;
}

const Rectangles operator+(Rectangles&& r, const Vector& v) {
    return move(Rectangles(move(r)) += v);
}

const Rectangles operator+(const Vector& v, Rectangles&& r) {
    return move(Rectangles(move(r)) += v);
}


Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.width() == rect2.width());
    assert(rect2.pos().x() == rect1.pos().x());
    assert(rect2.pos().y() == rect1.pos().y() + rect1.height());
    return Rectangle(rect1.width(),
                     rect1.height() + rect2.height(),
                     rect1.pos());
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.height() == rect2.height());
    assert(rect2.pos().x() == rect1.pos().x() + rect1.width());
    assert(rect2.pos().y() == rect1.pos().y());
    return Rectangle(rect1.width() + rect2.width(),
                     rect1.height(),
                     rect1.pos());
}

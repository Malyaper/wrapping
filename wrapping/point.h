#pragma once

struct Point {
    double x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

int orientation(const Point& p, const Point& q, const Point& r);

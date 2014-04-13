#ifndef POINT_H
#define POINT_H

#include <stdlib.h>

struct Point {
    size_t x, y;
    bool is_empty;
    Point(size_t xx, size_t yy, bool is_emp = false) : x(xx), y(yy), is_empty(is_emp) {}
    static Point Empty() { return Point(0, 0, true); }
};

#endif // POINT_H

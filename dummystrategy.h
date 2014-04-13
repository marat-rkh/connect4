#ifndef DUMMYSTRATEGY_H
#define DUMMYSTRATEGY_H

#include "field.h"
#include "strategy.h"
#include <cstdlib>

class DummyStrategy : public Strategy {
public:
    DummyStrategy() : current_column_(3) {}
    int MakeDecision(Field const& field) override;
private:
    int current_column_;
    const int DANGER_SEQ_LENGTH = 3;
    int step_ = -3;

    struct Point {
        size_t x, y;
        bool is_empty;
        Point(size_t xx, size_t yy, bool is_emp = false) : x(xx), y(yy), is_empty(is_emp) {}
        static Point Empty() { return Point(0, 0, true); }
    };

    Point CheckLines(Field const& field);
    Point CheckColumns(Field const& field);
    int DefauldDecision(Field const& field);
    Point CheckMatrixLines(Vector2d& matrix);
    Point CheckDangerLine(Vector2d& matrix, Point beg, Point end);
    Vector2d TramsposeMatrix(Vector2d const& matrix);
};

#endif // DUMMYSTRATEGY_H

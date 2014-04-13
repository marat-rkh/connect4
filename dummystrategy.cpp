#include "dummystrategy.h"

#include "field.h"

#include <algorithm>

int DummyStrategy::MakeDecision(Field const& field) {
    Point res = CheckColumns(field);
    if(!res.is_empty) {
        return res.x;
    }
    return DefauldDecision(field);
}

DummyStrategy::Point DummyStrategy::CheckLines(Field const& field) {
    Vector2d matrix = field.GetState();
    return CheckMatrixLines(matrix);
}

DummyStrategy::Point DummyStrategy::CheckColumns(Field const& field) {
    Vector2d matrix = field.GetState();
    Vector2d transposed = TramsposeMatrix(matrix);
    Point res = CheckMatrixLines(transposed);
    return res.is_empty ? res : Point(res.y, res.x);
}

int DummyStrategy::DefauldDecision(Field const& field) {
    if(current_column_ != field.WIDTH - 1) {
        while(field.ColumnEmptyPart(current_column_) == 0) {
            current_column_ += step_;
            step_ = 1;
        }
        while(current_column_ < field.WIDTH - 1 && field.Top(current_column_) == WHITE_MARK &&
              field.ColumnEmptyPart(current_column_) < DANGER_SEQ_LENGTH) {
            current_column_ += step_;
            step_ = 1;
        }
    }
    return current_column_;
}

DummyStrategy::Point DummyStrategy::CheckMatrixLines(Vector2d& matrix) {
    for(size_t i = 0; i != matrix.size(); ++i) {
        for(size_t j = 0; j != matrix[i].size() - DANGER_SEQ_LENGTH + 1; ++j) {
            auto pred = [](char sym){ return sym == WHITE_MARK; };
            if(std::all_of(matrix[i].begin() + j, matrix[i].begin() + j + DANGER_SEQ_LENGTH, pred)) {
                Point res = CheckDangerLine(matrix, Point(j, i), Point(j + DANGER_SEQ_LENGTH - 1, i));
                if(!res.is_empty) {
                    return res;
                }
            }
        }
    }
    return Point::Empty();
}

DummyStrategy::Point DummyStrategy::CheckDangerLine(Vector2d& matrix, Point beg, Point end) {
    if(beg.x != 0 && matrix[beg.y][beg.x - 1] == EMPTY_MARK) {
        return Point(beg.x - 1, beg.y);
    }
    if(end.x != matrix[0].size() && matrix[end.y][end.x + 1] == EMPTY_MARK) {
        return Point(end.x + 1, end.y);
    }
    return Point::Empty();
}

Vector2d DummyStrategy::TramsposeMatrix(Vector2d const& matrix) {
    Vector2d transposed(matrix[0].size(), Vector(matrix.size()));
    for (size_t i = 0; i < matrix[0].size(); i++) {
       for (size_t j = 0; j < matrix.size(); j++) {
           transposed[i][j] = matrix[j][i];
       }
    }
    return transposed;
}

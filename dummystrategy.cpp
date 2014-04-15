#include "dummystrategy.h"
#include "field.h"

#include <algorithm>

int DummyStrategy::MakeDecision(Field const& field) {
    int res = TryFindDangerInColumns(field);
    if(res >= 0) {
        return res;
    }
    res = TryFindDangerInLines(field);
    return res >= 0 ? res : DefauldDecision(field);
}

int DummyStrategy::TryFindDangerInColumns(Field const& field) {
    for(int i = 0; i != Field::WIDTH; ++i) {
        for(int j = 0; j != Field::HEIGHT - DANGER_SEQ_LENGTH + 1; ++j) {
            function<bool(Mark)> pred = [](Mark sym){ return sym == WHITE_MARK; };
            if(field.ColumnAllOf(i, j, j + DANGER_SEQ_LENGTH, pred) &&
               CheckDangerColumnPos(field, i, j + DANGER_SEQ_LENGTH)) {
                return i;
            }
        }
    }
    return -1;
}

int DummyStrategy::TryFindDangerInLines(Field const& field) {
    for(int i = 0; i != Field::WIDTH; ++i) {
        if(field.ColumnEmptyPart(i) != 0) {
            if(CheckLineLeft3(i, field) || CheckLineRight3(i, field) ||
               CheckLineLeft2(i, field) || CheckLineRight2(i, field)) {
                return i;
            }
        }
    }
    return -1;
}

bool DummyStrategy::CheckDangerColumnPos(Field const& field, int column, int line) {
    return line != field.HEIGHT && field.At(line, column) == EMPTY_MARK;
}

bool DummyStrategy::CheckLineLeft3(int col, Field const& field) {
    function<bool(Mark)> pred = [](Mark sym){ return sym == WHITE_MARK; };
    return (col - DANGER_SEQ_LENGTH >= 0) &&
           (field.LineAllOf(field.Top(col), col - DANGER_SEQ_LENGTH, col, pred));
}

bool DummyStrategy::CheckLineRight3(int col, Field const& field) {
    function<bool(Mark)> pred = [](Mark sym){ return sym == WHITE_MARK; };
    return (col + DANGER_SEQ_LENGTH + 1 < Field::WIDTH) &&
           (field.LineAllOf(field.Top(col), col + 1, col + DANGER_SEQ_LENGTH + 1, pred));
}

bool DummyStrategy::CheckLineLeft2(int col, Field const& field) {
    function<bool(Mark)> pred = [](Mark sym){ return sym == WHITE_MARK; };
    return (col - DANGER_SEQ_LENGTH >= 0) &&
           (field.LineAllOf(field.Top(col), col - DANGER_SEQ_LENGTH - 1, col, pred)) &&
           (field.At(field.Top(col), col - DANGER_SEQ_LENGTH) == EMPTY_MARK);
}

bool DummyStrategy::CheckLineRight2(int col, Field const& field) {
    function<bool(Mark)> pred = [](Mark sym){ return sym == WHITE_MARK; };
    return (col + DANGER_SEQ_LENGTH + 1 < Field::WIDTH) &&
           (field.LineAllOf(field.Top(col), col + 1, col + DANGER_SEQ_LENGTH, pred)) &&
           (field.At(field.Top(col), col + DANGER_SEQ_LENGTH + 1) == EMPTY_MARK);
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

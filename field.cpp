#include "field.h"

#include <algorithm>

using std::vector;

Field::Field() {
    array<Mark, WIDTH> empty_line;
    empty_line.fill(EMPTY_MARK);
    field_.fill(empty_line);
    tops_.fill(0);
}

bool Field::MakeMove(int pos, Mark mark) {
    if(pos > WIDTH) {
        return false;
    }
    if(tops_[pos] == HEIGHT) {
        return false;
    }
    field_[tops_[pos]][pos] = mark;
    tops_[pos] += 1;
    return true;
}

bool Field::LineAllOf(int line, int column_start, int column_end, function<bool (Mark)> const& pred) const {
    return AllOf(line, column_start, line + 1, column_end, 1, pred);
}

bool Field::ColumnAllOf(int column, int line_start, int line_end, function<bool (Mark)> const& pred) const {
    return AllOf(line_start, column, line_end, column + 1, Field::WIDTH, pred);
}

bool Field::AllOf(int lstart, int cstart, int lend, int cend, int step, function<bool (Mark)> const& pred) const {
    for(; lstart != lend; ++lstart) {
        for( ; cstart < cend; cstart += step) {
            if(!pred(field_[lstart][cstart])) {
                return false;
            }
        }
        cstart %= Field::WIDTH;
    }
    return true;
}

//bool Field::LineAllOf(int line, int column_start, int column_end, function<bool (Mark)> const& pred) const {
//    for(int i = column_start; i != column_end; ++i) {
//        if(!pred(field_[line][i])) {
//            return false;
//        }
//    }
//    return true;
//}

//bool Field::ColumnAllOf(int column, int line_start, int line_end, const function<bool (Mark)> &pred) const {
//    for(int i = line_start; i != line_end; ++i) {
//        if(!pred(field_[i][column])) {
//            return false;
//        }
//    }
//    return true;
//}

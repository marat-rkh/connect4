#include "field.h"

#include <algorithm>

using std::vector;

Field::Field() : field_(HEIGHT, vector<char>(WIDTH, EMPTY_MARK)) {
    std::fill(tops_, tops_ + WIDTH, 0);
}

bool Field::MakeMove(int pos, char mark) {
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

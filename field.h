#ifndef FIELD_H
#define FIELD_H

#include <array>
#include <functional>

using std::array;
using std::function;

enum Mark {EMPTY_MARK, BLACK_MARK, WHITE_MARK};

class Field {
public:
    Field();

    Mark At(int l, int c) const { return field_[l][c]; }
    Mark Top(int i) const {
        int line = (tops_[i] == 0) ? 0 : (tops_[i] - 1);
        return At(line, i);
    }
    int ColumnEmptyPart(int i) const { return HEIGHT - tops_[i]; }
    bool WhitesMove(int pos) { return MakeMove(pos, WHITE_MARK); }
    bool BlacksMove(int pos) { return MakeMove(pos, BLACK_MARK); }
    bool LineAllOf(int line, int column_start, int column_end, function<bool(Mark)> const& pred) const;
    bool ColumnAllOf(int column, int line_start, int line_end, function<bool(Mark)> const& pred) const;

    static const int HEIGHT = 6;
    static const int WIDTH = 7;
private:
    bool MakeMove(int pos, Mark mark);
    bool AllOf(int lstart, int cstart, int lend, int cend, int step, function<bool(Mark)> const& pred) const;

    array<array<Mark, WIDTH>, HEIGHT> field_;
    array<int, WIDTH> tops_;
};

#endif // FIELD_H

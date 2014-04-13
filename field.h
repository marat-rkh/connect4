#ifndef FIELD_H
#define FIELD_H

#include <vector>

using std::vector;

typedef vector<char> Vector;
typedef vector<vector<char> > Vector2d;

const char EMPTY_MARK = '0';
const char BLACK_MARK = '1';
const char WHITE_MARK = '2';

//enum Marks {EMPTY_MARK, BLACK_MARK, WHITE_MARK};

class Field {
public:
    Field();

    char At(int i, int j) const { return field_[i][j]; }
    char Top(int i) const {
        int line = tops_[i] == 0 ? 0 : tops_[i] - 1;
        return At(line, i);
    }
    int ColumnEmptyPart(int i) const { return HEIGHT - tops_[i]; }
    bool WhitesMove(int pos) { return MakeMove(pos, WHITE_MARK); }
    bool BlacksMove(int pos) { return MakeMove(pos, BLACK_MARK); }
    Vector2d const& GetState() const { return field_; }

    static const int HEIGHT = 6;
    static const int WIDTH = 7;
private:
    bool MakeMove(int pos, char mark);

    Vector2d field_;
    int tops_[WIDTH];
};

#endif // FIELD_H

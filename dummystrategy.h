#ifndef DUMMYSTRATEGY_H
#define DUMMYSTRATEGY_H

#include "field.h"
#include "strategy.h"

class DummyStrategy : public Strategy {
public:
    DummyStrategy() : current_column_(3) {}
    int MakeDecision(Field const& field) override;
private:
    int current_column_;
    const int DANGER_SEQ_LENGTH = 3;
    int step_ = -3;

    int TryFindDangerInColumns(Field const& field);
    int TryFindDangerInLines(Field const& field);
    bool CheckDangerColumnPos(Field const& field, int column, int line);
    bool CheckLineLeft3(int col, Field const& field);
    bool CheckLineRight3(int col, Field const& field);
    bool CheckLineLeft2(int col, Field const& field);
    bool CheckLineRight2(int col, Field const& field);
    int DefauldDecision(Field const& field);
};

#endif // DUMMYSTRATEGY_H

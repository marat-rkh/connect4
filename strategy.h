#ifndef STRATEGY_H
#define STRATEGY_H

class Field;

class Strategy {
public:
    virtual int MakeDecision(Field const& field) = 0;
    virtual ~Strategy() {}
};

#endif // STRATEGY_H

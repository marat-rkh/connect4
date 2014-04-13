#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "field.h"
class Strategy;

class GameController {
public:
    GameController(Strategy* strat);
    void Start(bool debug = false);
private:
    void PrintField();

    Strategy* strategy_;
    Field field_;
};

#endif // GAMECONTROLLER_H

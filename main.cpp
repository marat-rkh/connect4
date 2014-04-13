#include <iostream>

#include "gamecontroller.h"
#include "dummystrategy.h"

int main() {
    DummyStrategy dummy_strategy;
    GameController game_controller(&dummy_strategy);
    game_controller.Start(false);
    return 0;
}

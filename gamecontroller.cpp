#include "gamecontroller.h"

#include "strategy.h"
#include "field.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

GameController::GameController(Strategy *strat)
    : strategy_(strat)
{}

void GameController::Start(bool debug) {
    std::string first_command;
    cin >> first_command;
    if(first_command == "Go") {
        while(true) {
            int my_move = strategy_->MakeDecision(field_);
            field_.BlacksMove(my_move);
            cout << my_move << endl;
            int enemys_move;
            std::cin >> enemys_move;
            field_.WhitesMove(enemys_move);
            if(debug) {
                PrintField();
            }
        }
    }
    else {
        int enemys_move = std::stoi(first_command);
        while(true) {
            field_.WhitesMove(enemys_move);
            int my_move = strategy_->MakeDecision(field_);
            field_.BlacksMove(my_move);
            cout << my_move << endl;
            if(debug) {
                PrintField();
            }
            cin >> enemys_move;
        }
    }
}

void GameController::PrintField() {
    for(int i = 0; i != field_.HEIGHT; ++i) {
        for(int j = 0; j != field_.WIDTH; ++j) {
            cout << field_.At(i, j) << ' ';
        }
        cout << endl;
    }
}

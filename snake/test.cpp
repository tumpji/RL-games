#include <iostream>

#include "snake.h"

Direction get_user_direction() {
    char input;
    bool ok = false;
    while (not ok) {
        std::cin >> input;

        switch(input) {
            case 'u':
                return Direction::UP;
                ok = true;
                break;
            case 'd':
                return Direction::DOWN;
                ok = true;
                break;
            case 'l':
                return Direction::LEFT;
                ok = true;
                break;
            case 'r':
                return Direction::RIGHT;
                ok = true;
                break;
            default:
                break;
        }
    }
    return Direction::UP;
}

using namespace std;

int main () {
    Snake<> snake;

    while (not snake.game_finished()) {
        snake.debug_print();
        snake.next_iteration(get_user_direction());
    }
}

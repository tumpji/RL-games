#include <iostream>
#include <array>
#include <cassert>

/** class Position
 * stores information about position of figures
 */
template<int BOARD_SIZE_X, int BOARD_SIZE_Y>
class Position {
public:
    Position(): x(0), y(0) {}
    Position(int x, int y): x(x), y(y) {}
    Position(int v): x(v % BOARD_SIZE_Y), y(v / BOARD_SIZE_Y) {}

    bool on_board () { return x >= 0 and y >= 0 and x < BOARD_SIZE_X and y < BOARD_SIZE_Y; }
    
    bool operator== (Position p){ return x == p.x and y == p.y; }

public:
    int x, y;
};


/** class Direction
 * stores information about move of figure
 */
class Direction {
public:
    Direction(): x(0), y(0) {}
    Direction(int x, int y): x(x), y(y) {}

    template<int BOARD_SIZE_X, int BOARD_SIZE_Y>
    Position<BOARD_SIZE_X, BOARD_SIZE_Y> operator+(Position<BOARD_SIZE_X, BOARD_SIZE_Y> p) {
        p.x += x;
        p.y += y;
        return p;
    }

    int x, y;
    static Direction UP, DOWN, LEFT, RIGHT;
};

/** class Board
 * stores all 
 */
template<class Block, int BOARD_SIZE_X, int BOARD_SIZE_Y>
class Board {
protected:
    Board() { clean(); }
    void clean () { position.fill(Block()); }
    
    Block& get(Position<BOARD_SIZE_X, BOARD_SIZE_Y> p) {
        assert(on_board(p));
        return position[p.x + p.y*BOARD_SIZE_Y];
    }

public:
    void debug_print() {
        for (int a = 0; a < BOARD_SIZE_Y; ++a) {
            for (int b = 0; b < BOARD_SIZE_X; ++b) {
                std::cout << position[a*BOARD_SIZE_Y + b];
            }
            std::cout << "\n";
        }
    }
protected:
    std::array<Block, BOARD_SIZE_X*BOARD_SIZE_Y> position;
};

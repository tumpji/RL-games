#include <iostream>
#include <array>
#include <cassert>

template<int BOARD_SIZE=8>
class Position {
public:
    Position(): x(0), y(0) {check();}
    Position(int x, int y): x(x), y(y) {check();}
    Position(int v): x(v % BOARD_SIZE), y(v / BOARD_SIZE) {check();}

    inline void check() {assert(x >= 0 and y >= 0 and x < BOARD_SIZE and y < BOARD_SIZE);}

    bool operator== (Position p){ return x == p.x and y == p.y; }
public:
    int x, y;
};


class Direction {
public:
    Direction(): x(0), y(0) {}
    Direction(int x, int y): x(x), y(y) {}

    template<int BOARD_SIZE>
    Position<BOARD_SIZE> operator+(Position<BOARD_SIZE> p) {
        p.x += x;
        p.y += y;
        return p;
    }

    int x, y;
    static Direction UP, DOWN, LEFT, RIGHT;
};

template<class Block, int BOARD_SIZE=8>
class Board {
protected:
    Board() { clean(); }

    void clean () {
        position.fill(Block());
        //std::fill(position, position + BOARD_SIZE*BOARD_SIZE, 0);
    }

    bool on_board(Position<BOARD_SIZE> p) {
        if ( p.x < 0 or p.y < 0 or p.x >= BOARD_SIZE or p.y >= BOARD_SIZE )
            return false;
        return true;
    }
    Block& get(Position<BOARD_SIZE> p) {
        assert( on_board(p) );
        return position[p.x + p.y*BOARD_SIZE];
    }

public:
    void debug_print() {
        for (int a = 0; a < BOARD_SIZE; ++a) {
            for (int b = 0; b < BOARD_SIZE; ++b) {
                std::cout << position[a*BOARD_SIZE + b];
            }
            std::cout << std::endl;
        }
    }
protected:
    std::array<Block, BOARD_SIZE*BOARD_SIZE> position;
};

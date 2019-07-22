#include <random>
#include <cassert>
#include <ctime>

#include "board.h"

class SnakeDirection : public Direction {
public:
    SnakeDirection(): Direction(), item(0) {}
    SnakeDirection(Direction d): Direction(d), item(0) {}
     
    void set_food() {item =  1;}
    bool is_food() {return item == 1;}
    void clean() {item = 0;}

    bool empty_space () {return x == 0 and y == 0;}

    bool operator==(Direction d) { return d.x == x and d.y == y; }
private:
    // 1 = food; 0 = nothing
    int item;
};

template<int BOARD_SIZE_X, int BOARD_SIZE_Y, int NUM_FOOD=1>
class Snake: public Board<SnakeDirection, BOARD_SIZE_X, BOARD_SIZE_Y> {
public:
    Snake(): head(BOARD_SIZE_X/2, BOARD_SIZE_Y/2), tail(head), done(false), snake_size(1), generated_foods(0), 
        random_generator(std::time(nullptr)), distribution(0, BOARD_SIZE_X*BOARD_SIZE_Y-1) 
    { }

    bool game_finished () {return done;}
    
    int next_iteration(Direction dir) {
        assert(not done);
        int points = 0;
        SnakePosition new_head = SnakeDirection(dir) + head;
        SnakePosition new_tail;
        if (head == tail) 
            new_tail = SnakeDirection(dir) + tail;
        else 
            new_tail = this->get(tail) + tail;

        // hit  wall
        if (not new_head.on_board()) {
            done = true;
            return 0;
        }
        // hit itself
        else if (not this->get(new_head).empty_space()) {
            done = true;
            return 0;
        }
        else {
            this->get(head) = SnakeDirection(dir);
            head = new_head;
        }

        // hit food
        if (this->get(new_head).is_food()) {
            generated_foods -= 1;
            snake_size += 1;
            points += 1;
            this->get(new_head).clean();
        }
        // clear space - he is moving
        else {
            this->get(tail) = SnakeDirection(); 
            tail = new_tail;
        }

        if (generated_foods < NUM_FOOD) {
            find_random_empty_position().set_food();
            generated_foods += 1;
        }
        
        sanity_check();
        std::cout << new_head.x << " " << new_head.y << std::endl;
        return points;
    }

    void debug_print() {
        std::cout << "   " << head.x << " " << head.y << std::endl;
        std::cout << "##";
        for (int a = 0; a < BOARD_SIZE_X; ++a)
            std::cout << "#";
        std::cout << std::endl;

        for (int a = 0; a < BOARD_SIZE_Y; ++a) {
            std::cout << "|";
            for (int b = 0; b < BOARD_SIZE_X; ++b) {
                SnakeDirection d = this->get(SnakePosition(b,a));
                if ( d.empty_space() ) {
                    if ( a == head.y and b == head.x )
                        std::cout << "o";
                    else if ( d.is_food() )
                        std::cout << "F";
                    else
                        std::cout << " ";
                } else if ( d == Direction::UP ) {
                    std::cout << "8";
                } else if ( d == Direction::DOWN ) {
                    std::cout << "8";
                } else if ( d == Direction::LEFT ) {
                    std::cout << "=";
                } else if ( d == Direction::RIGHT ) {
                    std::cout << "=";
                }
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "##";
        for (int a = 0; a < BOARD_SIZE_X; ++a)
            std::cout << "#";
        std::cout << std::endl;
    }

    void sanity_check () {
        int san_n_size = 0, san_n_food = 0;
        for (int a = 0; a < BOARD_SIZE_X; ++a)
            for (int b = 0; b < BOARD_SIZE_Y; ++b)
            {
                SnakePosition p (a,b);
                SnakeDirection d = this->get(p);
                if (not d.empty_space())
                    san_n_size += 1;
                if (d.is_food())
                    san_n_food += 1;
            }
        assert(san_n_size + 1 == snake_size);
        assert(san_n_food == generated_foods);
    }

protected:
    SnakeDirection& find_random_empty_position () {

        assert(snake_size < BOARD_SIZE_X*BOARD_SIZE_Y);

        // first try
        for (int i = 0; i < 10; ++i) {
            SnakePosition p = SnakePosition(distribution(random_generator));
            if (p == head)
                continue;
            SnakeDirection& actual = this->get(p);
            if ( actual.empty_space() ) {
                return actual;
            }
        }

        // second try =
        //int target_found = std::uniform_int_distribution<int>(
        //        0, BOARD_SIZE*BOARD_SIZE-snake_size-1)(random_generator);
        int target_found = std::uniform_int_distribution<int>(
                0, BOARD_SIZE_X*BOARD_SIZE_Y-snake_size-1)(random_generator);
        int found = 0;
        for (int a = 0; a < BOARD_SIZE_X; ++a)
            for (int b = 0; b < BOARD_SIZE_Y; ++b)
            {
                SnakePosition pos(a,b);
                if (pos == head)
                    continue;
                SnakeDirection& actual = this->get(pos);
                if (actual.empty_space())
                    found += 1;
                if (found == target_found)
                    return actual;
            }

        throw;
    }

private:
    using SnakePosition = Position<BOARD_SIZE_X, BOARD_SIZE_Y>;
    SnakePosition head, tail;
    bool done;
    int snake_size, generated_foods;

    std::mt19937 random_generator;
    std::uniform_int_distribution<unsigned int> distribution;
};

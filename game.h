#ifndef GAME_H
#define GAME_H

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "rule.h"

static char game_txt[2] = {' ','x'};

class game
{
    friend class window;
    //friend void calc_m(game* gm, std::vector<std::vector<int>>& temp, int num, int total_threads);
public:
    game(int height_, int width_, rule* r_, bool boundary_ = false);

    game(const game&) = delete;

    void generate();
    void generate(const std::vector<std::vector<int>>& start);

    void step();

    void enable_multithreading(bool en, int amnt=4);
    void step_m();
    static void calc_m(game* g, std::vector<std::vector<int>>* data, int beg, int end);

    int operator() (int i, int j) const {return cells[i][j];}
    void operator++ (int) {multi_thread ? step_m() : step();}

    int height() const {return m;}
    int width() const {return n;}

private:
    std::vector<std::vector<int>> cells;
    const int m,n;
    bool boundary;

    bool multi_thread=false;
    int thread_num;

    rule* const r;
};

class game_classic : public game
{
public:
    game_classic(int height_, int width_, bool boundary_ = false)
        : game(height_, width_, &rl, boundary_) {}
private:
    rule_classic rl;
};

std::ostream& operator<< (std::ostream& os, const game& g);

#endif // GAME_H

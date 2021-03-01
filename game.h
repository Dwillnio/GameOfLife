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
public:
    game(int height_, int width_, rule* r_, bool boundary_ = true);

    game(const game&) = delete;

    void generate();
    void generate(const std::vector<std::vector<int>>& start);

    void step();

    int operator() (int i, int j) const {return cells[i][j];}
    void operator++ (int) {step();}

    int height() const {return m;}
    int width() const {return n;}

private:
    std::vector<std::vector<int>> cells;
    const int m,n;
    bool boundary;

    rule* const r;
};

class game_classic : public game
{
public:
    game_classic(int height_, int width_, bool boundary_ = true)
        : game(height_, width_, &rl, boundary_) {}
private:
    rule_classic rl;
};

std::ostream& operator<< (std::ostream& os, const game& g);

#endif // GAME_H

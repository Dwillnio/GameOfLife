#include "game.h"

#include <thread>
#include <chrono>

game::game(int height_, int width_, rule* r_, bool boundary_)
    : m(height_), n(width_),boundary(boundary_), r(r_)
{
    cells.resize(m, std::vector<int>(n,0));
}

void game::generate()
{
    srand(time(NULL));
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            cells[i][j] = rand()%2;
}

void game::generate(const std::vector<std::vector<int>>& start)
{
    cells = start;
}


int mod(int a, int b)
{
    int ret = a % b;
    if (ret < 0)
        ret += b;
    return ret;
}


#define DEBUG

void game::operator++ (int)
{
#ifdef DEBUG
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#endif

    multi_thread ? step_m() : step();

#ifdef DEBUG

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms\n";
#endif
}

//701
//682
//543
void game::step()
{
    std::vector<int> neighbours(9,0);
    std::vector<std::vector<int>> temp(cells);

    if(boundary){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                std::fill(neighbours.begin(),neighbours.end(), 0);
                neighbours[8] = cells[i][j];
                if(i>0){
                    neighbours[0] = cells[i-1][j];
                    if(j>0)
                        neighbours[7] = cells[i-1][j-1];
                    if(j<n-1)
                        neighbours[1] = cells[i-1][j+1];
                }
                if(i<m-1){
                    neighbours[4] = cells[i+1][j];
                    if(j>0)
                        neighbours[5] = cells[i+1][j-1];
                    if(j<n-1)
                        neighbours[3] = cells[i+1][j+1];
                }
                if(j<n-1)
                    neighbours[2] = cells[i][j+1];
                if(j>0)
                    neighbours[6] = cells[i][j-1];

                temp[i][j] = r->calculate(neighbours);
            }
        }
    } else {
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                //std::fill(neighbours.begin(),neighbours.end(), 0);
                neighbours[8] = cells[i][j];

//                neighbours[0] = cells[mod(i-1,m)][j];
//                neighbours[1] = cells[mod(i-1,m)][mod(j+1,n)];
//                neighbours[7] = cells[mod(i-1,m)][mod(j-1,n)];

//                neighbours[4] = cells[mod(i+1,m)][j];
//                neighbours[3] = cells[mod(i+1,m)][mod(j+1,n)];
//                neighbours[5] = cells[mod(i+1,m)][mod(j-1,n)];

//                neighbours[2] = cells[i][mod(j+1,n)];
//                neighbours[6] = cells[i][mod(j-1,n)];

                int im, ip, jm, jp;
                if(i==0) im = m-1;
                else im = i-1;
                if(i==m-1) ip = 0;
                else ip = i+1;
                if(j==0) jm = n-1;
                else jm = j-1;
                if(j==n-1) jp = 0;
                else jp = j+1;

                neighbours[0] = cells[im][j];
                neighbours[1] = cells[im][jp];
                neighbours[7] = cells[im][jm];

                neighbours[4] = cells[ip][j];
                neighbours[3] = cells[ip][jp];
                neighbours[5] = cells[ip][jm];

                neighbours[2] = cells[i][jp];
                neighbours[6] = cells[i][jm];

                temp[i][j] = r->calculate(neighbours);
            }
        }
    }

    cells = temp;
}

void game::enable_multithreading(bool en, int amnt)
{
    multi_thread = en;
    thread_num = amnt;
}

void game::calc_m(game* gm, std::vector<std::vector<int>>* temp, int num, int total_threads)
{
    std::vector<int> neighbours(9,0);
    game& g = *gm;

    for(int i=num; i<g.m; i+=total_threads){
        for(int j=0; j<g.n; j++){
            if(g.boundary){
                std::fill(neighbours.begin(),neighbours.end(), 0);
                neighbours[8] = g.cells[i][j];
                if(i>0){
                    neighbours[0] = g.cells[i-1][j];
                    if(j>0)
                        neighbours[7] = g.cells[i-1][j-1];
                    if(j<g.n-1)
                        neighbours[1] = g.cells[i-1][j+1];
                }
                if(i<g.m-1){
                    neighbours[4] = g.cells[i+1][j];
                    if(j>0)
                        neighbours[5] = g.cells[i+1][j-1];
                    if(j<g.n-1)
                        neighbours[3] = g.cells[i+1][j+1];
                }
                if(j<g.n-1)
                    neighbours[2] = g.cells[i][j+1];
                if(j>0)
                    neighbours[6] = g.cells[i][j-1];

                (*temp)[i][j] = g.r->calculate(neighbours);
            } else {
                neighbours[8] = g.cells[i][j];

//                neighbours[0] = g.cells[mod(i-1,g.m)][j];
//                neighbours[1] = g.cells[mod(i-1,g.m)][mod(j+1,g.n)];
//                neighbours[7] = g.cells[mod(i-1,g.m)][mod(j-1,g.n)];

//                neighbours[4] = g.cells[mod(i+1,g.m)][j];
//                neighbours[3] = g.cells[mod(i+1,g.m)][mod(j+1,g.n)];
//                neighbours[5] = g.cells[mod(i+1,g.m)][mod(j-1,g.n)];

//                neighbours[2] = g.cells[i][mod(j+1,g.n)];
//                neighbours[6] = g.cells[i][mod(j-1,g.n)];

                int im, ip, jm, jp;
                if(i==0) im = g.m-1;
                else im = i-1;
                if(i==g.m-1) ip = 0;
                else ip = i+1;
                if(j==0) jm = g.n-1;
                else jm = j-1;
                if(j==g.n-1) jp = 0;
                else jp = j+1;

                neighbours[0] = g.cells[im][j];
                neighbours[1] = g.cells[im][jp];
                neighbours[7] = g.cells[im][jm];

                neighbours[4] = g.cells[ip][j];
                neighbours[3] = g.cells[ip][jp];
                neighbours[5] = g.cells[ip][jm];

                neighbours[2] = g.cells[i][jp];
                neighbours[6] = g.cells[i][jm];

                (*temp)[i][j] = g.r->calculate(neighbours);
            }
        }
    }
}

void game::step_m()
{
    std::vector<std::vector<int>> temp(cells);

    std::vector<std::thread> threads;
    for(int i=0; i<thread_num; i++)
        threads.push_back(std::thread(calc_m,this, &temp, i, thread_num));
        //threads.push_back(std::thread(skip, 1));

    for(int i=0; i<(int)threads.size(); i++)
        threads[i].join();

    cells = temp;
}


std::ostream& operator<< (std::ostream& os, const game& g)
{
    for(int i=0; i<g.height(); i++){
        for(int j=0; j<g.width(); j++){
            os << game_txt[g(i,j)];
        }
        os << "\n";
    }

    return os;
}

#include "game.h"

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

                neighbours[0] = cells[mod(i-1,m)][j];
                neighbours[1] = cells[mod(i-1,m)][mod(j+1,n)];
                neighbours[7] = cells[mod(i-1,m)][mod(j-1,n)];

                neighbours[4] = cells[mod(i+1,m)][j];
                neighbours[3] = cells[mod(i+1,m)][mod(j+1,n)];
                neighbours[5] = cells[mod(i+1,m)][mod(j-1,n)];

                neighbours[2] = cells[i][mod(j+1,n)];
                neighbours[6] = cells[i][mod(j-1,n)];

                temp[i][j] = r->calculate(neighbours);
            }
        }
    }

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

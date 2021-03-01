#include "rule.h"
#include <algorithm>

int rule_classic::calculate(const std::vector<int>& neighbours)
{
    int sum = 0;
    for(int i=0; i<8; i++)
        sum += neighbours[i];
    if(sum == 3) return 1;
    if(sum == 2 && neighbours[8]) return 1;
    return 0;
}


int rule_lifelike::calculate(const std::vector<int>& neighbours)
{

    int sum = 0;
    for(int i=0; i<8; i++)
        sum += neighbours[i];

    if(neighbours[8]) {
        if(std::find(stay.begin(), stay.end(), sum) != stay.end()) return 1;
    } else {
        if(std::find(born.begin(), born.end(), sum) != born.end()) return 1;
    }
    return 0;
}

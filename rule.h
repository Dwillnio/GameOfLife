#ifndef RULE_H
#define RULE_H

#include <vector>

class rule
{
public:
    virtual int calculate(const std::vector<int>& neighbours) = 0;
};

class rule_classic : public rule
{
public:
    virtual int calculate(const std::vector<int>& neighbours);
};

class rule_lifelike : public rule
{
public:
    rule_lifelike(std::vector<int> stay_, std::vector<int> born_) : rule(), stay(stay_), born(born_) {}

    virtual int calculate(const std::vector<int>& neighbours);

private:
    std::vector<int> stay, born;
};



#endif // RULE_H

#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include "User.h"
class cellsChangedObserver{
    public:
        virtual void outputBonus(std::vector<User> &users, int steps) = 0;
        virtual void outputLog(std::vector<User> users, char order, int steps, int addScore) = 0;
};
#endif

#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
class cellsChangedObserver{
    public:
        virtual void outputBonus(vector<User> &users, int steps) = 0;
        virtual void outputLog(vector<User> users, char order, int steps, int addScore) = 0;
};
#endif

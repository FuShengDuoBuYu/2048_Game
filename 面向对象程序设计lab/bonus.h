#ifndef BONUS_H
#define BONUS_H
#include "Observer.h"
#include <cassert>
#include <sys/timeb.h>
#include "User.h"
#include <time.h>
#include <iostream>
#include <fstream>

unsigned long long currentTimeMillisec();

class bonusObserver: public cellsChangedObserver{
    public:
        //输出奖励日志
        void outputBonus(std::vector<User> &users, int steps);
        void outputLog(std::vector<User> users, char order, int steps, int addScore) {}

        bonusObserver(){}
        ~bonusObserver(){}
};
#endif //BONUS_H
#ifndef LOG_H
#define LOG_H
#include "Observer.h"
#include <fstream>
#include "User.h"
#include <ctime>
class logObserver : public cellsChangedObserver{
    public:
        void outputLog(std::vector<User> users, char order, int steps, int addScore);
        void outputBonus(std::vector<User> &users, int steps) {}

        logObserver(){}
        ~logObserver(){}
};
#endif
#ifndef CHEAT_H
#define CHEAT_H
#include <string>
#include <iostream>
#include <vector>
#include "User.h"
#include <string>
class Cheat{
    public:
        bool isCheated = false;
        bool waitingForCheated = false;
        std::string cheatString;
        std::string cheatOrder;
        std::string result;
        char directionChar = 'n';
        std::string beCheatedUsername;
        //设置cheat条件
        void setCheat(std::vector<User> users, int steps);
        //用户被cheat的提示
        std::string beCheated(int direction[]);

        Cheat(){}
        Cheat(std::string cheatString){
            this->cheatString = cheatString;
        }
        ~Cheat(){}
};
#endif //CHEAT_H
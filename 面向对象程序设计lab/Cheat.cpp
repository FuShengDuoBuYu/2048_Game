#ifndef CHEAT_CPP
#define CHEAT_CPP
#include <string>
#include <iostream>
#include <vector>
#include "User.cpp"
using namespace std;
class Cheat{
    public:
        bool isCheated = false;
        bool waitingForCheated = false;
        string cheatString;
        string cheatOrder;
        string result;
        char directionChar = 'n';
        string beCheatedUsername;
        void setCheat(vector<User> users,int steps){
            beCheatedUsername = users[steps % users.size()].getUsername();
            cheatOrder = cheatString.substr(2, cheatString.length() - 1);
            isCheated = true;
            waitingForCheated = true;
        }
        string beCheated(int direction[]){
            result = "";
            for (int i = 0; i <= 3; i++){
                if (direction[i] == 1){
                    switch (i){
                    case 0:
                        directionChar = 'w';
                        break;
                    case 1:
                        directionChar = 'z';
                        break;
                    case 2:
                        directionChar = 'a';
                        break;
                    case 3:
                        directionChar = 's';
                        break;
                    }
                }
            }
            string directionString(1,directionChar);
            string copyCheatOrder = cheatOrder;
            result = cheatOrder.append(",if you agree,input '").append(directionString).append("'");
            cheatOrder = copyCheatOrder;
            return result;
        }
        Cheat(){}

        Cheat(string cheatString){
            this->cheatString = cheatString;
        }
};
#endif
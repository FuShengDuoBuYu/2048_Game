#include "Cheat.h"
using namespace std;
void Cheat::setCheat(vector<User> users,int steps){
    beCheatedUsername = users[steps % users.size()].getUsername();
    cheatOrder = cheatString.substr(2, cheatString.length() - 1);
    isCheated = true;
    waitingForCheated = true;
}
string Cheat::beCheated(int direction[]){
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

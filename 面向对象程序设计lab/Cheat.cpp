#include "Cheat.h"
using namespace std;
void Cheat::setCheat(vector<User> users,int steps){
    beCheatedUsername = users[steps % users.size()].getUsername();
    //由于用了两个cin没有用getline,此时两个变量一样了,不用再截取子串
    cheatOrder = cheatString;
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
    //由于字符串append会修改原字符串,故存一个旧的字符串备份
    string copyCheatOrder = cheatOrder;
    result = cheatOrder.append(",if you agree,input '").append(directionString).append("'");
    cheatOrder = copyCheatOrder;
    return result;
}

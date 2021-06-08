#include "Settings.h"
using namespace std;
int Settings::chooseGameMode(){
    system("cls");
    //确定游戏人数模式
    cout << "--------------Game Start--------------" << endl
        << endl
        << "Please choose your game mode:" << endl
        << "1: Single player mode" << endl
        << "2: Double player mode" << endl
        << "Please enter the number of the corresponding mode:";
    char modeChar;
    cin >> modeChar;
    while(1){
        if(modeChar - '1' ==0 || modeChar - '2'== 0){
            gameMode = modeChar - '0';
            break;
        }
        else{
            cout << "The number is invalid" << endl
                << "Please enter the number of the corresponding mode:";
            cin >> modeChar;
        }
    }
    return gameMode;
}

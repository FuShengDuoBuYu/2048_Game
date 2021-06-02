#ifndef SETTINGS_CPP
#define SETTINGS_CPP
#include <iostream>
#include <stdlib.h>
using namespace std;
class Settings{
    public:
        int row;
        int col;
        int gameMode = 1;
        int endNum = 2048;
        void startLog(){
            log = true;
        }
        void startBonus(){
            bonus = true;
        }
        bool getLogStatus(){
            return log;
        }
        bool getBonusStatus(){
            return bonus;
        }
        void testEndNum(){
            endNum = 64;
            // cout << "change the end num" << endl;
        }
        int chooseGameMode(){
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
        Settings(int row,int col){
            this->row = row;
            this->col = col;
            // cout << "success get settings" << endl;
        }
        Settings(){}

    private:
        bool log = false;
        bool bonus = false;
        
};
#endif
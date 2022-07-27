#ifndef SETTINGS_CPP
#define SETTINGS_CPP
#include <iostream>
#include <cstdlib>
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
        }
        int chooseGameMode();
        Settings(int row,int col){
            this->row = row;
            this->col = col;
        }

        Settings(){}
        ~Settings(){}
    private:
        bool log = false;
        bool bonus = false;
        
};
#endif // SETTINGS_H
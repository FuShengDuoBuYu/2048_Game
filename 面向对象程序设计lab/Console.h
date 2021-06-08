#ifndef CONSOLE_H
#define CONSOLE_H
#include "Settings.h"
#include "CellsBorad.h"
#include "log.h"
#include "bonus.h"
#include <iostream>
#include <vector>
#include "Users.h"
#include "Cheat.h"
#include <cstring>
#include "FileHandle.h"
class Console{
    public:
        Settings s;
        Cheat cheat;
        CellsBorad cellsBorad;
        std::vector<User> Users;
        //获取命令行参数
        void getLaunch(int argc, char *argv[]);
        //打印欢迎页面
        void welcomePage();
        //处理命令行参数的函数
        void handleArgv(int argc, char *argv[]);
        //打印棋盘样式
        void printCellsBorad();
        //处理用户输入
        void userInput();
        //游戏结束调用的函数
        void endGame(int gameMode);

        Console(Settings ss){
            this->s = ss;
        }
        Console(){}
        ~Console(){}
};
#endif //CONSOLE_H
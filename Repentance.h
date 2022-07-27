#ifndef REPENTANCE_H
#define REPENTANCE_H
#include "Cell.h"
#include <vector>
#include <iostream>
#include "User.h"
#include <fstream>
#include <ctime>
#include <cstdio>
#include <io.h>
class Repentance{
    public:
        //记录第一步的标志
        bool recordFirstStatus = false;
        //各个步数的棋盘
        std::vector<std::vector<Cell>> allStepsCellsBorad;
        //各个步数的分数
        std::vector<int> allStepsScore;
        //记录棋盘
        void recordChessBorad(std::vector<Cell> currentChessBorad,int repentanceNum);
        //记录分数
        void recordScore(int currentScore,int repentanceNum);
        //悔棋棋盘
        void repentanceChessBorad(std::vector<Cell>& currentChessBorad);
        //悔棋分数
        void repentanceScore(std::vector<User> &Users,int steps);
        //打印悔棋提示
        char printRepentance(int repentanceNum);
        //悔棋log
        void repentanceLog(std::vector<User> &Users,int steps);
        Repentance(){}
        ~Repentance(){}
};
#endif //REPENTANCE_H
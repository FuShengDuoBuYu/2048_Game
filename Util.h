#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <string>
#include <ctime>
#include "Cell.h"
#include "User.h"
class Util{

    public :
        //获得一个乱序数组
        int *getRandArray(int length);
        //将一个string中含有的数字提取出来
        std::vector<int> stringToInt(std::string s);
        //比较两个棋盘是否一样
        bool boardChanged(std::vector<Cell> cells, std::vector<Cell> copyCells);
        
        Util(){};
        ~Util(){};
};
#endif //UTIL_H
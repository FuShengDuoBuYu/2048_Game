#include "Console.h"
using namespace std;
int main(int argc,char *argv[]){
    //获取游戏主体
    Console c(Settings(4,4));
    c.getLaunch(argc, argv);
    c.cellsBorad = CellsBorad(c.s.col, c.s.row);
    c.welcomePage();
    c.userInput();
    return 0;
} 
#include "lab2048.cpp"

using namespace std;
int main(int argc,char *argv[]){
    srand((unsigned)time(NULL));
    int ROW, COL;
    int endNum = 2048;
    //如果是测试模式,就把终结数字改为64
    ifTest(endNum);
    //用户选择单人模式(数字1)还是双人(数字2),
    int modeNum = welcomePage(ROW,COL);
    vector<Cell> cells = createCells(ROW,COL);
    //双方一共进行了多少步
    int steps = 0;
    vector<User> users = createUsers(modeNum);
    //打印棋盘
    printCells(cells,users,steps,modeNum,ROW,COL);
    //处理用户的输入
    userInput(cells,endNum,users,steps,modeNum,ROW,COL);
    return 0;
    
} 
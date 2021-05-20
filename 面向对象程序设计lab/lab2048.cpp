#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include "lab2048.h"
#include <cstdlib>
#include <fstream>
using namespace std;

//Cell类的方法实现
void Cell:: printCell(){
    //当格子是空时,就什么也不打印
    if(value == 0){
        cout << "|     ";
    }
    //对不同的数字长度打印不同的格式
    else{
        switch(getLength()){
            case 1: 
                cout << "|  " << value << "  ";
                break;
            case 2:
                cout << "| " << value << "  ";
                break;
            case 3:
                cout << "| " << value << " ";
                break;
            case 4:
                cout << "| " << value << "";
                break;
        }
    }
}
 
//Util类的方法实现
int* Util:: getRandArray(int length){
    srand((unsigned)time(NULL));
    int *randArr = new int[length];
    //先把数组顺序赋初值
    for(int i = 0;i < length;i++){
        randArr[i] = i;
    }
    //将数组随机打乱
    for (int i = length;i > 1;i--){
        int index,tmp;
        index = rand()%i;
        tmp = randArr[index];
        randArr[index] = randArr[i - 1];
        randArr[i - 1] = tmp;
    }
    return randArr;
}

vector<int> Util::stringToInt(string s){
    std::vector<int> intArray;
    int j = 0;
    for (int i = 0; i < s.length();i++){
        if(s[i] == ' '){
            int num = 0;
            for (int k = j; k < i;k++){
                int temp = s[k] - '0';
                for (int m = 0; m < i - k - 1;m++){
                    temp = temp * 10;
                }
                num += temp;
            }
            intArray.push_back(num);
            j = i + 1;   
        }
    }
    int num = 0;
    string sub = s.substr(j, s.length() - j);
    intArray.push_back(atoi(sub.c_str()));
    return intArray;
}

//其他方法的实现

//创建一定数量的空格子的方法
vector<Cell> createCells(int ROW,int COL){
    vector<Cell> cells;
    //创建格子初始值为0
    for(int i = 0;i < ROW * COL;i++){
        Cell c(0);
        cells.push_back(c);
    }
    //获取工具类
    Util u;
    //先获得数字2出现的随机位置顺序,并先显示两个2
    int* randArr = u.getRandArray(ROW*COL);
    for (int i = 0; i < 2;i++){
        cells[randArr[i]].changeValue(2);
    }
    return cells;
}

//打印出格子的内容和边框的方法
void printCells(vector<Cell> cells,vector<User> users,int steps,int modeNum,int ROW,int COL){
    //对每个格子打印成排
    for(int i = 0;i < cells.size();i++){
        //打印上下左右的边框
        if(i % COL == 0){
            //如果是第一行,那么不需要补足上一行最后的竖线
            if(i == 0){
                for (int i = 0; i < COL;i++){
                    cout << "+-----";
                }
                cout << "+" << endl;
            }
            //如果不是第一行,就需要补足上一行最后的竖线
            else{
                cout << "|" << endl;
                for (int i = 0; i < COL;i++){
                    cout << "+-----";
                }
                cout << "+" << endl;
            }
        }
        //打印格子的属性值
        cells[i].printCell();
    }
    //打印最后一行的底线
    cout << "|" << endl;
    for (int i = 0; i < COL;i++){
        cout << "+-----";
    }
    cout << "+" << endl;
    //打印用户的当前分数
    for (int i = 0; i < users.size();i++){
        cout << users[i].getUsername()
             << " current score is "
             << users[i].getScore() << endl;
    }
    //打印下一个用户该输入指令
    if(modeNum != 1){
        cout << "It is turn for " << users[(steps + 1) % (users.size())].getUsername() << endl;
    }
}

//处理用户输入指令的方法
void userInput(vector<Cell> &cells,int endNum,vector<User> &users,int &steps,int modeNum,int ROW,int COL){
    //是否使用过cheat的功能的标志
    bool cheated = false;
    bool setCheated = false;
    //挖陷阱的人的原始输入命令
    string cheatOrder;
    //提示给对手的命令
    string orderString,request;
    //下陷阱的用户
    int user;
start : getline(cin,cheatOrder);
    while(1){
        //当没有可移动方向的时候,就结束
        if(moveDirection(cells,users,ROW,COL,steps)[4] == 0){
            endGame(users,modeNum);
        }
        //当出现2048或者64时就退出
        for (int j = 0; j < ROW * COL;j++){
            if(cells[j].getValue() == endNum){
                printCells(cells,users,steps,modeNum,ROW,COL);
                endGame(users,modeNum);
            }
        }
        //获取用户输入的命令
        cout << "Please input your order:" << endl;
        getline(cin,cheatOrder);
        const char *orderArray = cheatOrder.c_str();
        char order = orderArray[0];
        //如果用户输入了c命令以cheat,就获取用户的命令参数并记录是谁cheat的
        if(order == 'c'){
            setCheated = true;
            request = cheatOrder.substr(2, cheatOrder.length() - 2);
            user = steps % 2;
        }
        //判断有几个方向可以移动,如果只有一个,那就把这个方向传过来
        updateCells(cells,order,users,steps,ROW,COL,modeNum);
        printCells(cells,users,steps,modeNum,ROW,COL);
        int* direction =  moveDirection(cells, users, ROW, COL, steps);
        char directionChar;
        if (direction[4] == 1 && steps%2 != user && cheated == false && setCheated == true){
            cheated = true;
            for (int i = 0; i < 3; i++){
                if (direction[i] == 1){
                    switch (i){
                    case 0:
                        directionChar = 'w';
                        break;
                    case 1:
                        directionChar = 's';
                        break;
                    case 2:
                        directionChar = 'a';
                        break;
                    case 3:
                        directionChar = 'd';
                        break;
                    }
                }
            }
            //获取提示被cheat用户的提示语句
            char tempCharArray[2] = {directionChar,'\0'};
            orderString = request+" if you agree,enter the '"+tempCharArray+"'";
            cout << orderString << endl;
            cout << "Please input your order:" << endl;
            cin >> order;
            //用户陷入被cheat的循环
            updateCells(cells,order,users,steps,ROW,COL,modeNum,orderString,directionChar);
            printCells(cells,users,steps,modeNum,ROW,COL);
            goto start;
        }
    }
}

//上下左右更新图的方法
void updateCells(vector<Cell> &cells,char order,vector<User> &users,int &steps,int ROW,int COL,int modeNum){
    vector<Cell> copyCells = cells;
    //在上下左右四个方向更新
    switch(order){
        case 'w':
            upUpdateCells(cells, users, ROW, COL, steps);
            break;
        case 's':
            downUpdateCells(cells, users, ROW, COL, steps);
            break;
        case 'a':
            leftUpdateCells(cells, users, ROW, COL, steps);
            break;
        case 'd':
            rightUpdateCells(cells, users, ROW, COL, steps);
            break;
        case 'c':{
            cout << endl;
            break;
        }
        default :
            cout << "Invalid order! Input again:" << endl;
    }
    //当细胞图真正发生改变时,才能生成一个2并且让步数加一
    bool changed = false;
    for (int i = 0; i < cells.size();i++){
        if(cells[i].getValue()!=copyCells[i].getValue()){
            createRand2(cells, users, modeNum);
            steps++;
            changed = true;
            break;
        }
    }
    //若是没有让棋盘发生变化,那么就是无效输入
    if(changed == false && order != 'c'){
        cout << "The operator has not changed the map, please input again:" << endl;
    }
    
}

//随机位置生成一个2的方法
int createRand2(vector<Cell> &cells,vector<User> &users,int modeNum){
    vector<int> nullPlace;
    //记录值为0的下标
    for (int i = 0; i < cells.size();i++){
        if(cells[i].getValue() == 0){
            nullPlace.push_back(i);
        }
    }
    //如果被填满了,就显示游戏结束
    if(nullPlace.size() == 0){
        endGame(users, modeNum);
    }
    //随机位置产生2
    else
    {
        int place = nullPlace[rand() % nullPlace.size()];
        cells[place].changeValue(2);
        return place;
    }
    return 0;
}

//判断是否进入测试模式
void ifTest(int &endNum){
    cout << "Input '-t' to choose test mode;" << endl;
    cout << "Input other orders to choose normal mode:" << endl;
    string order;
    cin >> order;
    if("-t" == order){
        endNum = 64;
    }
}

//选择进入单人模式还是双人模式以及确定维数的方法
int welcomePage(int &ROW,int &COL){
    //确定游戏模式
    system("cls");
    cout << "--------------Game Start--------------" << endl
         << endl
         << "Please choose your game mode:" << endl
         << "1: Single player mode" << endl
         << "2: Double player mode" << endl
         << "Please enter the number of the corresponding mode:";
    int modeNum;
    char modeChar;
    cin >> modeChar;
    while(1){
        if(modeChar == 49 || modeChar == 50){
            modeNum = modeChar - 48;
            break;
        }
        else{
            cout << "The number is invalid" << endl
                 << "Please enter the number of the corresponding mode:";
            cin >> modeChar;
        }
    }
    
    //确定游戏维数
    system("cls");
    cout << "Please enter the number of the corresponding dimension:";
    char gameDimension;
    cin >> gameDimension;
    while(1){
        if(gameDimension == 50 || gameDimension == 51 || gameDimension == 52 || gameDimension == 53){
            ROW = gameDimension - 48;
            COL = gameDimension - 48;
            break;
        }
        else{
            cout << "The number is invalid" << endl
                 << "Please enter the number of the corresponding dimension:";
            cin >> gameDimension;
        }
    }
    return modeNum;
}

//创建一定数量的用户的方法
vector<User> createUsers(int modeNum){
    vector<User> users;
    //创建用户
    for(int i = 0;i < modeNum;i++){
        if(modeNum == 2){
            cout << "Please input the username of player" << i+1 << endl;
            std::string username;
            cin >> username;
            User u = User(username, 0);
            users.push_back(u);
        }
        else{
            User u = User(" ", 0);
            users.push_back(u);
       }
    }
    system("cls");
    return users;
}

//结束游戏的方法
void endGame(std::vector<User> users,int modeNum){
    cout << endl << "=================================" << endl
         << "Game over!" << endl;
    //打印用户的最终分数
    for (int i = 0; i < users.size(); i++){
        cout << users[i].getUsername()
             << " final score is "
             << users[i].getScore() << endl;
    }
    //如果是双人,就计算得出胜负
    if(modeNum == 2){
        if(users[0].getScore() > users[1].getScore()){
            cout << endl << users[0].getUsername() << " win!" << endl;
        }
        if(users[0].getScore() < users[1].getScore()){
            cout << endl << users[1].getUsername() << " win!" << endl;
        }
        if(users[0].getScore() == users[1].getScore()){
            cout << "It ends in a draw" << endl;
        }
    }
    exit(0);
}

//判断移动方向的方法
int* moveDirection(vector<Cell> cells,std::vector<User> users, int ROW, int COL,int &steps){
    int directionNum = 0;
    int *direction = new int[5];
    for (int i = 0; i < 5;i++){
        direction[i] = 0;
    }
    vector<Cell> copyCells = cells;
    //调用一下函数检查更新后的细胞图是否和原来一致
    //向上判断
    upUpdateCells(copyCells, users, ROW, COL, steps);
    for (int i = 0; i < copyCells.size();i++){
        if(copyCells[i].getValue()!=cells[i].getValue()){
            directionNum++;
            direction[0] = 1;
            break;
        }
    }

    copyCells = cells;
    //向下判断
    downUpdateCells(copyCells, users, ROW, COL, steps);
    for (int i = 0; i < copyCells.size();i++){
        if(copyCells[i].getValue()!=cells[i].getValue()){
            directionNum++;
            direction[1] = 1;
            break;
        }
    }
    copyCells = cells;
    //向左判断
    leftUpdateCells(copyCells, users, ROW, COL, steps);
    for (int i = 0; i < copyCells.size();i++){
        if(copyCells[i].getValue()!=cells[i].getValue()){
            directionNum++;
            direction[2] = 1;
            break;
        }
    }
    copyCells = cells;
    //向右判断
    rightUpdateCells(copyCells, users, ROW, COL, steps);
    for (int i = 0; i < copyCells.size();i++){
        if(copyCells[i].getValue()!=cells[i].getValue()){
            directionNum++;
            direction[3] = 1;
            break;
        }
    }
    direction[4] = directionNum;
    return direction;
}

void upUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps){
    //对每一列依次向上进行合并和移动
    for (int i = 0; i < COL; i++)
    {
        //对第i列进行合并
        for (int j = 0; j < ROW-1;j++){
            for (int k = j + 1; k <= ROW-1;k++){
                //可以合并时
                if(cells[i+j*COL].getValue()==cells[i+k*COL].getValue() && cells[i+j*COL].getValue() !=0){
                    cells[i+j*COL].changeValue(2*cells[i+j*COL].getValue());
                    cells[i+k*COL].changeValue(0);
                    users[steps%(users.size())].setScore(users[steps%(users.size())].getScore() + cells[i + j * COL].getValue());
                    break;
                }
                //没有可以合并的
                if(cells[i+j*COL].getValue()!=0 && cells[i+k*COL].getValue()!=0 && cells[i+j*COL].getValue()!=cells[i+k*COL].getValue()){
                    break;
                }
            }
        }
        // 对第i列进行移动
        for (int j = 1; j <= ROW-1;j++){
            for (int k = 0; k < j;k++){
                if(cells[i+k*COL].getValue()==0){
                    cells[i+k*COL].changeValue(cells[i+j*COL].getValue());
                    cells[i+j*COL].changeValue(0);
                    break;
                }
            }
        }
    }
}

void downUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps){
    //对每一列依次向下进行合并和移动
    for (int i = 0; i < COL;i++){
        //对第i列进行合并
        for (int j = ROW-1; j > 0;j--){
            for (int k = j - 1; k >= 0;k--){
                if(cells[i+j*COL].getValue()==cells[i+k*COL].getValue() && cells[i+j*COL].getValue() !=0){
                    cells[i+j*COL].changeValue(2*cells[i+j*COL].getValue());
                    cells[i+k*COL].changeValue(0);
                    users[steps%(users.size())].setScore(users[steps%(users.size())].getScore() + cells[i+j*COL].getValue());
                    break;
                }
                if(cells[i+j*COL].getValue()!=0 && cells[i+k*COL].getValue()!=0 && cells[i+j*COL].getValue()!=cells[i+k*COL].getValue()){
                    break;
                }
            }
        }
        // 对第i列进行移动
        for (int j = ROW-2; j >= 0;j--){
            for (int k = ROW - 1; k > j;k--){
                if(cells[i+k*COL].getValue()==0){
                    cells[i+k*COL].changeValue(cells[i+j*COL].getValue());
                    cells[i+j*COL].changeValue(0);
                    break;
                }
            }
        }
    }
}

void leftUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps){
    //对每一行依次向左进行合并和移动
    for (int i = 0; i < ROW;i++){
        //对第i行进行合并
        for (int j = 0; j < COL - 1;j++){
            for (int k = j + 1; k <=COL-1;k++){
                if(cells[i*ROW+j].getValue()==cells[i*ROW+k].getValue() && cells[i*ROW+j].getValue() !=0){
                    cells[i * ROW + j].changeValue(2*cells[i * ROW + j].getValue());
                    cells[i * ROW + k].changeValue(0);
                    users[steps%(users.size())].setScore(users[steps%(users.size())].getScore() + cells[i * ROW + j].getValue());
                    break;
                }
                if(cells[i*ROW+j].getValue()!=0 && cells[i*ROW+k].getValue()!=0 && cells[i*ROW+j].getValue()!=cells[i*ROW+k].getValue()){
                    break;
                }
            }
        }
        // 对第i行进行移动
        for (int j = 1; j <=COL-1;j++){
            for (int k = 0; k < j;k++){
                if(cells[i*ROW+k].getValue()==0){
                    cells[i * ROW + k].changeValue(cells[i * ROW + j].getValue());
                    cells[i * ROW + j].changeValue(0);
                    break;
                }
            }
        }
    }
}

void rightUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps){
    //对每一行依次向右进行合并和移动
    for (int i = 0; i < ROW;i++){
        //对第i行进行合并
        for (int j = COL-1; j > 0;j--){
            for (int k = j - 1; k >= 0;k--){
                if(cells[i*ROW+j].getValue()==cells[i*ROW+k].getValue() && cells[i*ROW+j].getValue() !=0){
                    cells[i * ROW + j].changeValue(2*cells[i * ROW + j].getValue());
                    cells[i * ROW + k].changeValue(0);
                    users[steps%(users.size())].setScore(users[steps%(users.size())].getScore() + cells[i * ROW + j].getValue());
                    break;
                }
                if(cells[i*ROW+j].getValue()!=0 && cells[i*ROW+k].getValue()!=0 && cells[i*ROW+j].getValue()!=cells[i*ROW+k].getValue()){
                    break;
                }
            }
        }
        // 对第i行进行移动
        for (int j = COL-2; j >= 0;j--){
            for (int k = COL - 1; k > j;k--){
                if(cells[i*ROW+k].getValue()==0){
                    cells[i * ROW + k].changeValue(cells[i * ROW + j].getValue());
                    cells[i * ROW + j].changeValue(0);
                    break;
                }
            }
        }
    }
}
//重载的更新棋盘的方法
void updateCells(vector<Cell> &cells,char order,vector<User> &users,int &steps,int ROW,int COL,int modeNum,string orderString,char directionChar){
    //仅在指定位置上更新
    while(1){
        //若用户进入陷阱,就按照这个唯一的方向更新棋盘图
        if(order == directionChar){
            steps++;
            switch(order){
                case 'w' :
                    upUpdateCells(cells,users,ROW,COL,steps);
                    break;
                case 's' :
                    downUpdateCells(cells,users,ROW,COL,steps);
                    break;
                case 'a' :
                    leftUpdateCells(cells, users, ROW, COL, steps);
                    break;
                case 'd' :
                    rightUpdateCells(cells, users, ROW, COL, steps);
                    break;
            }
            createRand2(cells,users,modeNum);
            break;
        }
        else{
            cout << "The order is invalid, please input again:" << endl << orderString << endl;
            cin >> order;
        }
    }
}

//读取文件内容的方法
vector<string> readFiles(string filename){
    vector<string> fileContent;
    ifstream in(filename);
    string s;
    //第i行
    int i = 0;
    while (getline(in, s)){
        fileContent.push_back(s);
    }
    return fileContent;
}

//处理输入的文件中的信息
char handleMessageInFile(vector<string> fileContent,int &ROW,int &COL,vector<Cell> &cells){
    //第一行的维数
    for (int i = 0; i < fileContent[0].length();i++){
        if(fileContent[0][i]>='1' && fileContent[0][i]<='9'){
            ROW = COL = fileContent[0][i] - '0';
        }
        break;
    }
    
    //第2行到第k+1行的棋盘数据
    //TODO::这里需要一个string中找数字的方法
    vector<int> values;
    Util u;
    for (int i = 1; i < ROW + 1; i++){
        values = u.stringToInt(fileContent[i]);
        for (int j = 0; j < values.size();j++){
            cells.push_back(Cell(values[j]));
        }
    }
    char moveDirection;
    //最后一行的移动方向
    for (int i = 0; i < fileContent[fileContent.size()-1].length();i++){
        if(fileContent[fileContent.size()-1][i]>='a' && fileContent[fileContent.size()-1][i]<='z'){
            moveDirection = fileContent[fileContent.size()-1][i];
        }
        else if(fileContent[fileContent.size()-1][i]>='A' && fileContent[fileContent.size()-1][i]<='Z'){
            moveDirection = fileContent[fileContent.size()-1][i] - 'a';
        }
        break;
    }
    //返回要移动的方向
    
    return moveDirection;
}

//获取最后写入文件的数据
vector<string> resultFile(char moveDirections,vector<Cell> cells,vector<User> users,int ROW,int COL){
    vector<string> resultString;
    int fakeSteps = 3;
    int *direction = moveDirection(cells, users, ROW, COL, fakeSteps);
    //第一行的string
    string directions;
    directions = to_string(direction[4]);
    if (direction[0] == 1){
        directions.append(" w");
    }
    if(direction[1]==1){
        directions.append(" a");
    }
    if(direction[3]==1){
        directions.append(" s");
    }
    if(direction[2]==1){
        directions.append(" z");
    }
    resultString.push_back(directions);
    //棋盘的string
    //先更新棋盘
    switch (moveDirections){
        case 'w': upUpdateCells(cells,users, ROW, COL, fakeSteps);
            break;
        case 'a': leftUpdateCells(cells,users, ROW, COL, fakeSteps);
            break;
        case 'z': downUpdateCells(cells,users, ROW, COL, fakeSteps);
            break;
        case 's': rightUpdateCells(cells,users, ROW, COL, fakeSteps);
            break;
    }
    //再写入数组
    for (int i = 0; i < ROW;i++){
        string row = "";
        for (int j = 0; j < COL;j++){
            if(j == COL - 1){
                row.append(to_string(cells[i * ROW + j].getValue()));
            }
            else{
                row.append(to_string(cells[i * ROW + j].getValue()));
                row.append(" ");
            }
        }
        resultString.push_back(row);
    }
    //随机产生的一个2
    resultString.push_back("2");
    //找到随机生成2的位置
    int randomPlace = createRand2(cells, users, 1);
    string coordinate = to_string(randomPlace / ROW) + " " + to_string(randomPlace % COL);
    resultString.push_back(coordinate);
    //获取获得的分数
    resultString.push_back(to_string(users[0].getScore()));
    return resultString;
}
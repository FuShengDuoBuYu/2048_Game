#include <string>
#include <iostream>
#include <cstring>
// #include "lab.h"
using namespace std;
class Chess{   
    int value;
    public :
        //修改格子的属性值
        void setValue(int value){
            this->value = value;
        }
        //获取格子里数字的位数
        int getLength(){
            std::string s = to_string(value);
            return s.length();
        }
        int getValue(){
            return value;
        }
        Chess(int value){
            this->value = value;
        };
        ~Chess(){};
};

//关于比赛的各个设定的信息类
class Settings{
    int row;
    public:
        int col;
        void setRow(int row){
            this->row = row;
        }
        void setCol(int col){
            this->col = col;
        }
        Settings(){};
        ~Settings(){};
};

//有关棋盘的各个数据的类
class Chessboard{
    Settings s;
    public:
        Chessboard(){};
        ~Chessboard(){};
};

//衔接用户输入和棋盘的控制台类
class Console{
    Settings s;
    public:
        //开始游戏,打印欢迎界面并等待用户输入
        void gameStart(char *argv[]);
        Console(Settings &s){
            this->s = s;
        }
};

int main(int argc,char *argv[]){
    Settings s;
    Console c(s);
    c.gameStart(argv);
    cout << s.col;
}   

void Console:: gameStart(char *argv[]){
    if(strcmp("-t",argv[1]) == 0){
        s.setCol(3);
        s.setRow(3);
    }
}
#ifndef LAB2048_H
#define LAB2048_H
using namespace std;
class Cell
{

    int value;

    public :
        //打印出格子的内容以及部分边框
        void printCell();
        //修改格子的属性值
        void changeValue(int currentValue){
            value = currentValue;
        }
        //获取格子里数字的位数
        int getLength(){
            int length = 0;
            int copyValue = value;
            while(copyValue!=0){
                copyValue = copyValue / 10;
                length++;
            }
            return length;
        }
        int getValue(){
            return value;
        }
        Cell(int value){
            this->value = value;
        };
        ~Cell(){};
};

class Util{

    public :
        //获得一个乱序数组
        int *getRandArray(int length);
        Util(){};
        ~Util(){};
        vector<int> stringToInt(string s);
};

class User{
    string username;
    int score;

    public:
        string getUsername(){
            return this->username;
        }
        void setScore(int score){
            this->score = score;
        }
        int getScore(){
            return this->score;
        }
        User(string username, int score){
            this->username = username;
            this->score = score;
        };
        ~User(){};

};

//方法声明
void printCells(vector<Cell> cells,vector<User> users,int steps,int modeNum,int ROW,int COL);
vector<Cell> createCells(int ROW,int COL);
void userInput(vector<Cell> &cells,int endNum,vector<User> &users,int &steps,int modeNum,int ROW,int COL,bool log,bool bonus);
void updateCells(vector<Cell> &cells,char order,vector<User> &users,int &steps,int ROW,int COL,int modeNum,bool log,bool bonus);
int createRand2(vector<Cell> &cells,vector<User> &users,int modeNum);
void ifTest(int &endNum);
int welcomePage(int &ROW,int &COL);
vector<User> createUsers(int modeNum);
void endGame(vector<User> users,int modeNum);
int upUpdateCells(vector<Cell> &cells, vector<User> &users, int ROW, int COL,int &steps);
int downUpdateCells(vector<Cell> &cells, vector<User> &users, int ROW, int COL,int &steps);
int leftUpdateCells(vector<Cell> &cells, vector<User> &users, int ROW, int COL,int &steps);
int rightUpdateCells(vector<Cell> &cells, vector<User> &users, int ROW, int COL,int &steps);
int* moveDirection(vector<Cell> cells, vector<User> users, int ROW, int COL, int &steps);
void updateCells(vector<Cell> &cells,char order,vector<User> &users,int &steps,int ROW,int COL,int modeNum,string orderString,char directionChar,bool log,bool bonus);
vector<string> readFiles(string filename);
char handleMessageInFile(vector<string> fileContent, int &ROW, int &COL, vector<Cell> &cells);
vector<string> resultFile(char moveDirections,vector<Cell> cells,vector<User> users,int ROW,int COL);
#endif
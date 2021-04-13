#ifndef LAB2048_H
#define LAB2048_H
class Cell{

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
};

class User{
    std:: string username;
    int score;

    public:
        std:: string getUsername(){
            return this->username;
        }
        void setScore(int score){
            this->score = score;
        }
        int getScore(){
            return this->score;
        }
        User(std:: string username, int score){
            this->username = username;
            this->score = score;
        };
        ~User(){};

};

//方法声明
void printCells(std::vector<Cell> cells,std::vector<User> users,int steps,int modeNum,int ROW,int COL);
std::vector<Cell> createCells(int ROW,int COL);
void userInput(std::vector<Cell> &cells,int endNum,std::vector<User> &users,int &steps,int modeNum,int ROW,int COL);
void updateCells(std::vector<Cell> &cells,char order,std::vector<User> &users,int &steps,int ROW,int COL,int modeNum);
void createRand2(std::vector<Cell> &cells,std::vector<User> &users,int modeNum);
void ifTest(int &endNum);
int welcomePage(int &ROW,int &COL);
std::vector<User> createUsers(int modeNum);
void endGame(std::vector<User> users,int modeNum);
void upUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
void downUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
void leftUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
void rightUpdateCells(std::vector<Cell> &cells, std::vector<User> &users, int ROW, int COL,int &steps);
int* moveDirection(std::vector<Cell> cells, std::vector<User> users, int ROW, int COL, int &steps);
void updateCells(std::vector<Cell> &cells,char order,std::vector<User> &users,int &steps,int ROW,int COL,int modeNum,std::string orderString,char directionChar);
#endif
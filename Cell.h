#ifndef CELL_H
#define CELL_H
#include <iostream>
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
        int getLength();
        int getValue(){
            return value;
        }
        Cell(int value){
            this->value = value;
        };
        ~Cell(){};
};
#endif //CELL_H
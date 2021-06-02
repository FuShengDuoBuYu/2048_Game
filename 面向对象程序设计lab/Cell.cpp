#include <iostream>
#ifndef CELL_CPP
#define CELL_CPP
class Cell
{
    int value;
    public :
        //打印出格子的内容以及部分边框
        void printCell(){
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
#endif
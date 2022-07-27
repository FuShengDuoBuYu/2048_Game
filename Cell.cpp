#include "Cell.h"

using namespace std;
void Cell::printCell(){
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

int Cell::getLength(){
    int length = 0;
    int copyValue = value;
    while(copyValue!=0){
        copyValue = copyValue / 10;
        length++;
    }
    return length;
}

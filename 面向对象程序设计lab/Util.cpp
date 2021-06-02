#ifndef UTIL_CPP
#define UTIL_CPP
#include <vector>
#include <string>
#include <time.h>
#include "Cell.cpp"
#include "User.cpp"
using namespace std;
class Util{

    public :
        //获得一个乱序数组
        int* getRandArray(int length){
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

        vector<int> stringToInt(string s){
            vector<int> intArray;
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
        
        //比较两个棋盘是否一样
        bool boardChanged(vector<Cell> cells,vector<Cell> copyCells){
            // cout << cells.size();
            for (int i = 0; i < cells.size();i++){
                if(cells[i].getValue()!=copyCells[i].getValue()){
                    return true;
                }
                
            }
            return false;
        }
        Util(){};
        ~Util(){};
        
};
#endif 
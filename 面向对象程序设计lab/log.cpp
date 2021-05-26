#include "log.h"
#include <vector>
#include <string>
#include <assert.h>
using namespace std;

void outputLog(vector<User> users,char order,int steps,int addScore){
    //获取当前时间字符串
    time_t t = time(0);
    char time[64];
    strftime(time, sizeof(time), "%Y/%m/%d/%H:%M:%S", localtime(&t));
    ofstream out("log.txt",ios::app);
    string direction;
    switch(order){
        case 'w' :
            direction = "上";
            break;
        case 'a' :
            direction = "左";
            break;
        case 's' :
            direction = "右";
            break;
        case 'z' :
            direction = "下";
            break;
    }
    if(users.size() == 1){
        out << "移动得分: " << "默认用户 " << time << " " << direction << " " << addScore << endl;
    }
    else if(users.size() == 2){
        out << "移动得分: " << users[steps%2].getUsername() << " " << time << " " << direction << " " << addScore << endl;
    }
}
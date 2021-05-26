#include "bonus.h"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include <sys/timeb.h>
#include <time.h>
using namespace std;

//获取当前距离1970年的毫秒数
unsigned long long lastMilltime = 0;

unsigned long long currentTimeMillisec(){
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}


//输出奖励日志
void outputBonus(vector<User> &users,int steps){
    //获取不含毫秒的时间
    time_t t = time(0);
    char time[64];
    strftime(time, sizeof(time), "%Y/%m/%d/%H:%M:%S", localtime(&t));
    //获取含毫秒的时间
    unsigned long long nowMilltime = currentTimeMillisec();
    //当间隔小于1s时
    if((nowMilltime - lastMilltime) < 1000){
        //输出奖励日志并加和总分
        ofstream out("log.txt",ios::app);
        if(users.size() == 1){
            //输出日志
            out << "奖励得分: " << "默认用户 " << time << " 0." 
            << (nowMilltime - lastMilltime)/100 << " 1" << endl;
            //总分加1
            users[0].setScore(users[0].getScore() + 1);
        }
        else if(users.size() == 2){
            //输出日志
            out << "奖励得分: " << users[(steps+1)%2].getUsername() << " " 
            << time << " 0." << (nowMilltime - lastMilltime)/100 << " 1" << endl;
            //总分加1
            users[(steps+1)%2].setScore(users[(steps+1)%2].getScore() + 1);
        }
    }
    lastMilltime = nowMilltime;
}
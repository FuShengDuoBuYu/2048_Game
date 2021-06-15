#include "Repentance.h"
using namespace std;
void Repentance::recordChessBorad(std::vector<Cell> currentChessBorad,int repentanceNum){
    allStepsCellsBorad.push_back(currentChessBorad);
    if(allStepsCellsBorad.size() > repentanceNum+2){
        allStepsCellsBorad.erase(allStepsCellsBorad.begin());
    }
    // cout << "==cellsboard==" << allStepsCellsBorad.size() << endl;
}

void Repentance::recordScore(int currentScore,int repentanceNum){
    allStepsScore.push_back(currentScore);
    if(allStepsScore.size() > repentanceNum+4){
        allStepsScore.erase(allStepsScore.begin());
    }
}

void Repentance::repentanceChessBorad(std::vector<Cell>& currentChessBorad){
    currentChessBorad = allStepsCellsBorad[allStepsCellsBorad.size()-2];
    allStepsCellsBorad.pop_back();
}

void Repentance::repentanceScore(std::vector<User>& Users,int steps){
    if(allStepsScore[allStepsScore.size() - 2] != allStepsScore[allStepsScore.size() - 1]){
        repentanceLog(Users,steps);
    }
    if(Users.size() == 1){
        Users[steps % Users.size()].setScore(allStepsScore[allStepsScore.size()-2]);
        allStepsScore.pop_back();
    }else{
        Users[steps % Users.size()].setScore(allStepsScore[allStepsScore.size()-3]);
        allStepsScore.pop_back();
    }
    
}

char Repentance::printRepentance(int repentanceNum){
    if(repentanceNum > 0){
        char repentanceOrder;
        cout << "You still have " << repentanceNum << " chances to repent,do you want to repent?(y/n)" << endl;
        while(1){
            cin >> repentanceOrder;
            if(repentanceOrder == 'y' || repentanceOrder == 'n'){
                return repentanceOrder;
            }
            else{
                cout << "Please input 'y' or 'n':" << endl;
            }
        }
    }
    else{
        return ' ';
    }
}

void Repentance::repentanceLog(std::vector<User>& Users,int steps){
    if(access("log.txt",0) != -1){
        //获取当前时间字符串
        time_t t = time(0);
        char time[64];
        strftime(time, sizeof(time), "%Y/%m/%d/%H:%M:%S", localtime(&t));
        ofstream out("log.txt",ios::app);
        if(Users.size() == 1){
            out << "悔棋扣除得分: 默认用户 " << time << " " << allStepsScore[allStepsScore.size() - 2] - allStepsScore[allStepsScore.size() - 1] << endl;
        }
        else{
            out << "悔棋扣除得分: " << Users[steps % Users.size()].getUsername() << " " << time << " "
            << allStepsScore[allStepsScore.size() - 3] - allStepsScore[allStepsScore.size() - 1] << endl;
        }
    }
}
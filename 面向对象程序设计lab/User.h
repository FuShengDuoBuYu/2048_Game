#ifndef USER_H
#define USER_H
#include <string>
class User{
    std::string username;
    int score;

    public:
        std::string getUsername(){
            return this->username;
        }
        void setScore(int score){
            this->score = score;
        }
        int getScore(){
            return this->score;
        }
        void addScore(int addScore){
            score += addScore;
        }
        
        User(std::string username, int score){
            this->username = username;
            this->score = score;
        };
        ~User(){};

};
#endif
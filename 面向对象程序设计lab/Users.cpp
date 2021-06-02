#ifndef USERS_CPP
#define USERS_CPP
#include "User.cpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class UsersVector{
    public:
    vector<User> users;
    //创建一定数量的用户的方法
    vector<User> createUsers(int gameMode){
        //创建用户
        for(int i = 0;i < gameMode;i++){
            if(gameMode == 2){
                cout << "Please input the username of player" << i+1 << endl;
                string username;
                cin >> username;
                users.push_back(User(username, 0));
            }
            else{
                User u = User(" ", 0);
                users.push_back(u);
        }
        }
        system("cls");
        return users;
    }
    UsersVector(){}
    UsersVector(int gameMode){
        this->users = createUsers(gameMode);
    }
    
};
#endif
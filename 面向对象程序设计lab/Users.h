#ifndef USERS_H
#define USERS_H
#include "User.h"
#include <vector>
#include <string>
#include <iostream>

class UsersVector{
    public:
    std::vector<User> users;
    //创建一定数量的用户的方法
    std::vector<User> createUsers(int gameMode);
    
    UsersVector(){}
    UsersVector(int gameMode){
        this->users = createUsers(gameMode);
    }
    ~UsersVector(){}
    
};
#endif //USERS_H
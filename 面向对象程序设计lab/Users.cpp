#include "Users.h"
using namespace std;
vector<User> UsersVector::createUsers(int gameMode){
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
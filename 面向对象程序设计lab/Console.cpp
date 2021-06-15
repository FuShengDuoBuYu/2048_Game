#include "Console.h"
using namespace std;

void Console::getLaunch(int argc,char *argv[]){
    handleArgv(argc, argv);
}
void Console::welcomePage(){
    s.chooseGameMode();
    Users = UsersVector(s.gameMode).users;
    printCellsBorad();
}
//处理命令行参数的函数
void Console::handleArgv(int argc,char *argv[]){
    for (int i = 1; i < argc;i++){
        //测试条件-t
        if(strcmp("-t", argv[i]) == 0){
            s.testEndNum();
        }
        //棋盘维数2,3,4,5
        if(strcmp("-s", argv[i]) == 0){
            if(strcmp("2", argv[i+1])==0 ||strcmp("3", argv[i+1])==0 ||strcmp("4", argv[i+1])==0 ||strcmp("5", argv[i+1])==0){
                s.col = s.row = argv[i + 1][0] - '0';
            }
            else{
                cout << "please input the dimension of 3 4 or 5" << endl;
                exit(0);
            }
        }
        //直接输出文件
        if(strcmp("-i", argv[i]) == 0){
            if ((argc - i) >= 3 && strcmp("-o", argv[i + 2]) == 0){
                FileHandle fh(argv[i + 1],argv[i + 3]);
                vector<string> content = fh.readFiles(argv[i + 1]);
                char moveDirection = fh.handleMessageInFile(content, fh.row, fh.col);
                
                vector<string> resultString = fh.resultFile(moveDirection,fh.row,fh.col);
                fh.outputFile(resultString);
                exit(0);

            }
        }
        //开启log功能
        if(strcmp("-log",argv[i]) == 0){
            s.startLog();
        }
        //开启bonus功能
        if(strcmp("-p",argv[i]) == 0){
            s.startBonus();
        }
    }
}
//打印棋盘样式
void Console::printCellsBorad(){
    //对每个格子打印成排
    for(int i = 0;i < cellsBorad.cells.size();i++){
        //打印上下左右的边框
        if(i % s.col == 0){
            //如果是第一行,那么不需要补足上一行最后的竖线
            if(i == 0){
                for (int i = 0; i < s.col;i++){
                    cout << "+-----";
                }
                cout << "+" << endl;
            }
            //如果不是第一行,就需要补足上一行最后的竖线
            else{
                cout << "|" << endl;
                for (int i = 0; i < s.col;i++){
                    cout << "+-----";
                }
                cout << "+" << endl;
            }
        }
        //打印格子的属性值
        cellsBorad.cells[i].printCell();
    }
    //打印最后一行的底线
    cout << "|" << endl;
    for (int i = 0; i < s.col;i++){
        cout << "+-----";
    }
    cout << "+" << endl;
    //打印用户的当前分数
    for (int i = 0; i < Users.size();i++){
        cout << Users[i].getUsername() << " current score is " << Users[i].getScore() << endl;
    }
    //判断是不是死棋
    if(cellsBorad.deadBoard(s.endNum) == true || cellsBorad.moveDirection(s.row,s.col)[4] == 0){
        endGame(s.gameMode);
    }
    
    //考虑悔棋
    if(cellsBorad.steps != 0 && (cellsBorad.steps!= Users[cellsBorad.steps % Users.size()].repentanceStep&& s.gameMode == 2 || s.gameMode == 1) ){
        char repentanceOrder = r.printRepentance(Users[(cellsBorad.steps+1)%Users.size()].repentanceNum);
        //确定悔棋
        if(repentanceOrder == 'y'){
            //可悔棋次数减一
            Users[(cellsBorad.steps+1)%Users.size()].repentanceNum--;
            //修改棋盘,用户得分和游戏步数
            r.repentanceChessBorad(cellsBorad.cells);
            r.repentanceScore(Users, cellsBorad.steps);
            cellsBorad.steps--;
            //打印棋盘
            Users[cellsBorad.steps % Users.size()].repentanceStep = cellsBorad.steps;
            printCellsBorad();
        }else{
            if(s.gameMode != 1){
                cout << "It is turn for " << Users[(cellsBorad.steps+1) % (Users.size())].getUsername() << endl;
            }
        }
    }else{
        if(s.gameMode != 1){
                cout << "It is turn for " << Users[(cellsBorad.steps+1) % (Users.size())].getUsername() << endl;
        }
    }

    //考虑Cheat
    if(cellsBorad.moveDirection(s.row,s.col)[4] == 1 && Users[cellsBorad.steps%Users.size()].getUsername() != cheat.beCheatedUsername && cheat.waitingForCheated == true){
        cout << cheat.beCheated(cellsBorad.moveDirection(s.row, s.col)) << endl;
    }
    
    
}
void Console::userInput(){
    char order;
    Util u;
    string inputString;
    string inputString2;
    while(1){
        cout << "please input your order:" << endl;
        cin >> inputString2;
        if(inputString2 == "c"){
            cin >> inputString;
        }    
        order = inputString2.c_str()[0];
        if(order == 'w' ||order == 'a' ||order == 's' ||order == 'z'){
            //更改cheat状态
            if(order == cheat.directionChar && cheat.waitingForCheated == true){
                cheat.waitingForCheated = false;
            }
            else if(order != cheat.directionChar&& cellsBorad.moveDirection(s.row,s.col)[4] == 1 && Users[cellsBorad.steps%Users.size()].getUsername() != cheat.beCheatedUsername && cheat.waitingForCheated == true){
                cout << "Your order has not changed the chessboard" << endl;
                continue;
            }
            int addScores = 0;
            vector<Cell> copyCells = cellsBorad.cells;
            addScores = cellsBorad.updateBorad(order, s.row, s.col);
            Users[cellsBorad.steps % Users.size()].addScore(addScores);
            //输出log
            if(addScores != 0 && s.getLogStatus() == true){
                logObserver lo;
                lo.outputLog(Users,order,cellsBorad.steps,addScores);
            }
            //输出bonus
            if(u.boardChanged(copyCells,cellsBorad.cells) && s.getLogStatus() && s.getBonusStatus()){
                bonusObserver bo;
                bo.outputBonus(Users,cellsBorad.steps);
            }
            //记录悔棋棋盘和用户得分
            if(u.boardChanged(copyCells,cellsBorad.cells)){
                if(cellsBorad.steps == 1 && r.recordFirstStatus == false){
                    r.recordChessBorad(copyCells,Users[cellsBorad.steps%Users.size()].repentanceNum);
                    for (int i = 0; i < s.gameMode;i++){
                        r.recordScore(0,Users[cellsBorad.steps%Users.size()].repentanceNum);
                    }
                    r.recordFirstStatus = true;
                }
                r.recordChessBorad(cellsBorad.cells,Users[cellsBorad.steps%Users.size()].repentanceNum);
                r.recordScore(Users[cellsBorad.steps % Users.size()].getScore(),Users[cellsBorad.steps%Users.size()].repentanceNum);
            }
            printCellsBorad();
        }
        else if(order == 'c' && cheat.isCheated == false){
            if(s.gameMode == 1){
                cout << "Please use 'c' order in double player mode." << endl;
            }
            else{
                cheat = Cheat(inputString);
                cheat.setCheat(Users, cellsBorad.steps);
            }
        }
        else{
            cout << "The order has been input is invalid." << endl;
        }
    }
}
void Console::endGame(int gameMode){
    cout << endl << "=================================" << endl
        << "Game over!" << endl;
    //打印用户的最终分数
    for (int i = 0; i < Users.size(); i++){
        cout << Users[i].getUsername()
            << " final score is "
            << Users[i].getScore() << endl;
    }
    //如果是双人,就计算得出胜负
    if(gameMode == 2){
        if(Users[0].getScore() > Users[1].getScore()){
            cout << endl << Users[0].getUsername() << " win!" << endl;
        }
        if(Users[0].getScore() < Users[1].getScore()){
            cout << endl << Users[1].getUsername() << " win!" << endl;
        }
        if(Users[0].getScore() == Users[1].getScore()){
            cout << "It ends in a draw" << endl;
        }
    }
    exit(0);
}
        

#include "lab2048.cpp"
#include "log.cpp"

using namespace std;
int main(int argc,char *argv[]){
    srand((unsigned)time(NULL));
    int ROW, COL;
    int endNum = 2048;
    vector<Cell> cells;
    vector<User> users;
    bool log = false;
    bool bonus = false;
    //双方一共进行了多少步
    int steps = 0;
    for (int i = 1; i < argc;i++){
        //从文件中读取数据
        if(strcmp("-i", argv[i]) == 0){
            if ((argc - i) >= 3 && strcmp("-o", argv[i + 2]) == 0){
                users.push_back(User("", 0));
                vector<string> fileContent = readFiles(argv[i+1]);
                char moveDirection = handleMessageInFile(fileContent, ROW, COL, cells);
                vector<string> resultString = resultFile(moveDirection, cells, users, ROW, COL);
                //写入文件数据
                ofstream out(argv[i+3]);
                for (int i = 0; i < resultString.size(); i++)
                {
                    out << resultString[i] << endl;
                }
                cout << "The file has been created successfully!" << endl;
                out.close();
            }
            return 0;
        }
        else if(strcmp("-log",argv[i]) == 0){
            log = true;
        }
        else if(strcmp("-p",argv[i]) == 0){
            bonus = true;
        }
    }
    
    //如果是测试模式,就把终结数字改为64
    ifTest(endNum);
    //用户选择单人模式(数字1)还是双人(数字2),
    int modeNum = welcomePage(ROW,COL);
    cells = createCells(ROW,COL);
    users = createUsers(modeNum);
    //打印棋盘
    printCells(cells,users,steps,modeNum,ROW,COL);
    //处理用户的输入
    userInput(cells,endNum,users,steps,modeNum,ROW,COL,log,bonus);
    return 0;
} 
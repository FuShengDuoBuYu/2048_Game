#include "lab2048.cpp"

using namespace std;
int main(int argc,char *argv[]){
    srand((unsigned)time(NULL));
    int ROW, COL;
    int endNum = 2048;
    vector<Cell> cells;
    vector<User> users;
    //双方一共进行了多少步
    int steps = 0;
    //从文件中读取数据
    if(argc>=5 && strcmp("-i",argv[1]) == 0 && strcmp("-o",argv[3]) == 0){
        users.push_back(User("", 0));
        vector<string> fileContent = readFiles(argv[2]);
        char moveDirection = handleMessageInFile(fileContent, ROW, COL,cells);
        vector<string> resultString = resultFile(moveDirection,cells,users,ROW,COL);
        //写入文件数据
        ofstream out(argv[4]);
        for (int i = 0; i < resultString.size();i++){
            out << resultString[i] << endl;
        }
        cout << "The file has been created successfully!" << endl;
        out.close();
    }
    else{
        //如果是测试模式,就把终结数字改为64
        ifTest(endNum);
        //用户选择单人模式(数字1)还是双人(数字2),
        int modeNum = welcomePage(ROW,COL);
        cells = createCells(ROW,COL);
        users = createUsers(modeNum);
        //打印棋盘
        printCells(cells,users,steps,modeNum,ROW,COL);
        //处理用户的输入
        userInput(cells,endNum,users,steps,modeNum,ROW,COL);
        }
    return 0;
} 
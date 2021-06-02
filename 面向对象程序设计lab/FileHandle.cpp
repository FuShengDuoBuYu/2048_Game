#ifndef FILEHANDLE
#define FILEHANDLE
#include "Cell.cpp"
#include "User.cpp"
#include "Util.cpp"
#include "CellsBorad.cpp"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class FileHandle{
    public:
        CellsBorad cb = CellsBorad();
        int row = 0;
        int col = 0;
        //读取文件内容的方法
        vector<string> readFiles(string inputFilename){
            vector<string> fileContent;
            ifstream in(inputFilename);
            string s;
            //第i行
            int i = 0;
            while (getline(in, s)){
                if(s == "")
                    break;
                fileContent.push_back(s);
            }
            return fileContent;
        }

        //处理输入的文件中的信息
        char handleMessageInFile(vector<string> fileContent,int &ROW,int &COL){
            //第一行的维数
            for (int i = 0; i < fileContent[0].length();i++){
                if(fileContent[0][i]>='1' && fileContent[0][i]<='9'){
                    ROW = COL = fileContent[0][i] - '0';
                }
                break;
            }
            
            //第2行到第k+1行的棋盘数据
            //这里需要一个string中找数字的方法
            vector<int> values;
            Util u;
            for (int i = 1; i < ROW + 1; i++){
                values = u.stringToInt(fileContent[i]);
                for (int j = 0; j < values.size();j++){
                    cells.push_back(Cell(values[j]));
                }
            }
            char moveDirection;
            //最后一行的移动方向
            for (int i = 0; i < fileContent[fileContent.size()-1].length();i++){
                if(fileContent[fileContent.size()-1][i]>='a' && fileContent[fileContent.size()-1][i]<='z'){
                    moveDirection = fileContent[fileContent.size()-1][i];
                }
                else if(fileContent[fileContent.size()-1][i]>='A' && fileContent[fileContent.size()-1][i]<='Z'){
                    moveDirection = fileContent[fileContent.size()-1][i] - 'a';
                }
                break;
            }
            cb.cells = this->cells;
            //返回要移动的方向
            return moveDirection;
        }

        //获取最后写入文件的数据
        vector<string> resultFile(char moveDirections,int ROW,int COL){
            vector<string> resultString;
            int *direction = cb.moveDirection(ROW, COL);
            //第一行的string
            string directions;
            directions = to_string(direction[4]);
            if (direction[0] == 1){
                directions.append(" w");
            }
            if(direction[1]==1){
                directions.append(" a");
            }
            if(direction[3]==1){
                directions.append(" s");
            }
            if(direction[2]==1){
                directions.append(" z");
            }
            resultString.push_back(directions);
            //棋盘的string
            //先更新棋盘
            int addScore = 0;
            switch (moveDirections){
                case 'w': 
                    addScore+=cb.upUpdateCells(ROW, COL);
                    break;
                case 'a': 
                    addScore+=cb.leftUpdateCells(ROW, COL);
                    break;
                case 'z': 
                    addScore+=cb.downUpdateCells(ROW, COL);
                    break;
                case 's': 
                    addScore+=cb.rightUpdateCells(ROW, COL);
                    break;
            }
            //再写入数组
            for (int i = 0; i < ROW;i++){
                string row = "";
                for (int j = 0; j < COL;j++){
                    if(j == COL - 1){
                        row.append(to_string(cb.cells[i * ROW + j].getValue()));
                    }
                    else{
                        row.append(to_string(cb.cells[i * ROW + j].getValue()));
                        row.append(" ");
                    }
                }
                resultString.push_back(row);
            }
            //随机产生的一个2
            resultString.push_back("2");
            //找到随机生成2的位置
            int randomPlace = cb.createRand2(cb.cells);
            string coordinate = to_string(randomPlace / ROW) + " " + to_string(randomPlace % COL);
            resultString.push_back(coordinate);
            //获取获得的分数
            resultString.push_back(to_string(addScore));
            return resultString;
        }
        void outputFile(vector<string> resultString){
            ofstream out(outputFilename);
                for (int i = 0; i < resultString.size(); i++)
                {
                    out << resultString[i] << endl;
                }
                cout << "The file has been created successfully!" << endl;
                out.close();
        }
        //构造函数
        FileHandle(string inputFilename,string outputFilename){
            this->inputFilename = inputFilename;
            this->outputFilename = outputFilename;
        }
        FileHandle(){}
    private:
        vector<Cell> cells;
        vector<User> users;
        string inputFilename;
        string outputFilename;
};
#endif
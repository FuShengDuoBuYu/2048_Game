#ifndef FILEHANDLE_H
#define FILEHANDLE_H
#include "Cell.h"
#include "User.h"
#include "Util.h"
#include "CellsBorad.h"
#include <string>
#include <vector>
#include <fstream>
class FileHandle{
    public:
        CellsBorad cb = CellsBorad();
        int row = 0;
        int col = 0;
        //读取文件内容的方法
        std::vector<std::string> readFiles(std::string inputFilename);
        //处理输入的文件中的信息
        char handleMessageInFile(std::vector<std::string> fileContent, int &ROW, int &COL);
        //获取最后写入文件的数据
        std::vector<std::string> resultFile(char moveDirections, int ROW, int COL);
        //将文件输出到指定目标文件
        void outputFile(std::vector<std::string> resultString);
        
        FileHandle(std::string inputFilename,std::string outputFilename){
            this->inputFilename = inputFilename;
            this->outputFilename = outputFilename;
        }
        FileHandle(){}
        ~FileHandle(){}
    private:
        std::vector<Cell> cells;
        std::vector<User> users;
        std::string inputFilename;
        std::string outputFilename;
};
#endif //FILEHANDLE_H
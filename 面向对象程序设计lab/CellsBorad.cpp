#ifndef CELLSBORAD_CPP
#define CELLSBORAD_CPP

#include <vector>
#include "Util.cpp"
#include "Cell.cpp"
using namespace std;
class CellsBorad{
    public:
        int steps = 0;
        vector<Cell> cells;
        //创建初始棋盘
        vector<Cell> createCells(int ROW,int COL){
            //创建格子初始值为0
            for(int i = 0;i < ROW * COL;i++){
                Cell c(0);
                cells.push_back(c);
            }
            //获取工具类
            Util u;
            //先获得数字2出现的随机位置顺序,并先显示两个2
            int* randArr = u.getRandArray(ROW*COL);
            for (int i = 0; i < 2;i++){
                cells[randArr[i]].changeValue(2);
            }
            return cells;
        }
        int updateBorad(char order,int ROW,int COL){
            vector<Cell> copyCells = cells;
            int addScore = 0;
            //在上下左右四个方向更新
            switch(order){
                case 'w':
                    addScore += upUpdateCells(ROW, COL);
                    break;
                case 'z':
                    addScore += downUpdateCells(ROW, COL);
                    break;
                case 'a':
                    addScore += leftUpdateCells(ROW, COL);
                    break;
                case 's':
                    addScore += rightUpdateCells(ROW, COL);
                    break;
                case 'c':{
                    cout << endl;
                    break;
                }
            }
            Util u;
            // cout << u.boardChanged(cells, copyCells);
            if(u.boardChanged(cells,copyCells) == true){
                createRand2(cells);
                steps++;
            }
                       

            else{
                cout << "Your order has not change the board." << endl;
            }
            return addScore;
        }
        //随机位置生成一个2的方法
        int createRand2(vector<Cell> &cells){
            vector<int> nullPlace;
            //记录值为0的下标
            for (int i = 0; i < cells.size();i++){
                if(cells[i].getValue() == 0){
                    nullPlace.push_back(i);
                }
            }
            //如果被填满了,就显示游戏结束
            if(nullPlace.size() == 0){
                return -1;
            }
            //随机位置产生2
            else
            {
                int place = nullPlace[rand() % nullPlace.size()];
                cells[place].changeValue(2);
                return place;
            }
            return 0;
        }
        int upUpdateCells(int ROW, int COL){
            int addScore = 0;
            //对每一列依次向上进行合并和移动
            for (int i = 0; i < COL; i++)
            {
                //对第i列进行合并
                for (int j = 0; j < ROW-1;j++){
                    for (int k = j + 1; k <= ROW-1;k++){
                        //可以合并时
                        if(cells[i+j*COL].getValue()==cells[i+k*COL].getValue() && cells[i+j*COL].getValue() !=0){
                            cells[i+j*COL].changeValue(2*cells[i+j*COL].getValue());
                            cells[i + k * COL].changeValue(0);
                            addScore += cells[i + j * COL].getValue();
                            break;
                        }
                        //没有可以合并的
                        if(cells[i+j*COL].getValue()!=0 && cells[i+k*COL].getValue()!=0 && cells[i+j*COL].getValue()!=cells[i+k*COL].getValue()){
                            break;
                        }
                    }
                }
                // 对第i列进行移动
                for (int j = 1; j <= ROW-1;j++){
                    for (int k = 0; k < j;k++){
                        if(cells[i+k*COL].getValue()==0){
                            cells[i+k*COL].changeValue(cells[i+j*COL].getValue());
                            cells[i+j*COL].changeValue(0);
                            break;
                        }
                    }
                }
            }
            return addScore;
        }

        int downUpdateCells(int ROW, int COL){
            int addScore = 0;
            //对每一列依次向下进行合并和移动
            for (int i = 0; i < COL;i++){
                //对第i列进行合并
                for (int j = ROW-1; j > 0;j--){
                    for (int k = j - 1; k >= 0;k--){
                        if(cells[i+j*COL].getValue()==cells[i+k*COL].getValue() && cells[i+j*COL].getValue() !=0){
                            cells[i+j*COL].changeValue(2*cells[i+j*COL].getValue());
                            cells[i+k*COL].changeValue(0);
                            addScore += cells[i + j * COL].getValue();
                            break;
                        }
                        if(cells[i+j*COL].getValue()!=0 && cells[i+k*COL].getValue()!=0 && cells[i+j*COL].getValue()!=cells[i+k*COL].getValue()){
                            break;
                        }
                    }
                }
                // 对第i列进行移动
                for (int j = ROW-2; j >= 0;j--){
                    for (int k = ROW - 1; k > j;k--){
                        if(cells[i+k*COL].getValue()==0){
                            cells[i+k*COL].changeValue(cells[i+j*COL].getValue());
                            cells[i+j*COL].changeValue(0);
                            break;
                        }
                    }
                }
            }
            return addScore;
        }

        int leftUpdateCells(int ROW, int COL){
            int addScore = 0;
            //对每一行依次向左进行合并和移动
            for (int i = 0; i < ROW;i++){
                //对第i行进行合并
                for (int j = 0; j < COL - 1;j++){
                    for (int k = j + 1; k <=COL-1;k++){
                        if(cells[i*ROW+j].getValue()==cells[i*ROW+k].getValue() && cells[i*ROW+j].getValue() !=0){
                            cells[i * ROW + j].changeValue(2*cells[i * ROW + j].getValue());
                            cells[i * ROW + k].changeValue(0);
                            addScore += cells[i * ROW + j].getValue();
                            break;
                        }
                        if(cells[i*ROW+j].getValue()!=0 && cells[i*ROW+k].getValue()!=0 && cells[i*ROW+j].getValue()!=cells[i*ROW+k].getValue()){
                            break;
                        }
                    }
                }
                // 对第i行进行移动
                for (int j = 1; j <=COL-1;j++){
                    for (int k = 0; k < j;k++){
                        if(cells[i*ROW+k].getValue()==0){
                            cells[i * ROW + k].changeValue(cells[i * ROW + j].getValue());
                            cells[i * ROW + j].changeValue(0);
                            break;
                        }
                    }
                }
            }
            return addScore;
        }

        int rightUpdateCells(int ROW, int COL){
            int addScore = 0;
            //对每一行依次向右进行合并和移动
            for (int i = 0; i < ROW;i++){
                //对第i行进行合并
                for (int j = COL-1; j > 0;j--){
                    for (int k = j - 1; k >= 0;k--){
                        if(cells[i*ROW+j].getValue()==cells[i*ROW+k].getValue() && cells[i*ROW+j].getValue() !=0){
                            cells[i * ROW + j].changeValue(2*cells[i * ROW + j].getValue());
                            cells[i * ROW + k].changeValue(0);
                            addScore += cells[i * ROW + j].getValue();
                            break;
                        }
                        if(cells[i*ROW+j].getValue()!=0 && cells[i*ROW+k].getValue()!=0 && cells[i*ROW+j].getValue()!=cells[i*ROW+k].getValue()){
                            break;
                        }
                    }
                }
                // 对第i行进行移动
                for (int j = COL-2; j >= 0;j--){
                    for (int k = COL - 1; k > j;k--){
                        if(cells[i*ROW+k].getValue()==0){
                            cells[i * ROW + k].changeValue(cells[i * ROW + j].getValue());
                            cells[i * ROW + j].changeValue(0);
                            break;
                        }
                    }
                }
            }
            return addScore;
        }
        CellsBorad(){}
        CellsBorad(int row,int col){
            this->cells = createCells(row,col);
        }
        bool deadBoard(int endNum){
            for (int i = 0; i < cells.size();i++){
                if(cells[i].getValue() == endNum){
                    return true;
                }
            }
            return false;
        }
        
        //判断移动方向的方法
        int* moveDirection(int ROW, int COL){
            int directionNum = 0;
            int *direction = new int[5];
            for (int i = 0; i < 5;i++){
                direction[i] = 0;
            }
            vector<Cell> copyCells = cells;
            //调用一下函数检查更新后的细胞图是否和原来一致
            //向上判断
            upUpdateCells(ROW, COL);
            for (int i = 0; i < copyCells.size();i++){
                if(copyCells[i].getValue()!=cells[i].getValue()){
                    directionNum++;
                    direction[0] = 1;
                    break;
                }
            }
            cells = copyCells;
            //向下判断
            downUpdateCells(ROW, COL);
            for (int i = 0; i < copyCells.size();i++){
                if(copyCells[i].getValue()!=cells[i].getValue()){
                    directionNum++;
                    direction[1] = 1;
                    break;
                }
            }
            cells = copyCells;
            //向左判断
            leftUpdateCells(ROW, COL);
            for (int i = 0; i < copyCells.size();i++){
                if(copyCells[i].getValue()!=cells[i].getValue()){
                    directionNum++;
                    direction[2] = 1;
                    break;
                }
            }
            cells = copyCells;
            //向右判断
            rightUpdateCells(ROW, COL);
            for (int i = 0; i < copyCells.size();i++){
                if(copyCells[i].getValue()!=cells[i].getValue()){
                    directionNum++;
                    direction[3] = 1;
                    break;
                }
            }
            direction[4] = directionNum;
            cells = copyCells;
            return direction;
        }
};
#endif
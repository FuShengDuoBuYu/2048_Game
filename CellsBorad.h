#ifndef CELLSBORAD_H
#define CELLSBORAD_H

#include <vector>
#include "Util.h"
#include "Cell.h"
#include "Repentance.h"
class CellsBorad{

public:
    int steps = 0;
    std::vector<Cell> cells;
    //创建初始棋盘
    std::vector<Cell> createCells(int ROW, int COL);
    //更新棋盘
    int updateBorad(char order, int ROW, int COL);
    //随机位置生成一个2的方法
    int createRand2(std::vector<Cell> &cells);
    //上下左右更新棋盘方法
    int upUpdateCells(int ROW, int COL);
    int downUpdateCells(int ROW, int COL);
    int leftUpdateCells(int ROW, int COL);
    int rightUpdateCells(int ROW, int COL);
    //判断移动方向的方法
    int *moveDirection(int ROW, int COL);
    //判断是否已经是死棋
    bool deadBoard(int endNum);

    CellsBorad() {}
    CellsBorad(int row, int col)
    {
        this->cells = createCells(row, col);
        }
        ~CellsBorad(){}
};
#endif //CELLSBORAD_H
#include <string>
using namespace std;
typedef int DataType;

/**
 * 队列接口
 */
class IQueue {
public:
    virtual ~IQueue(){};

    // 若队列未满，将 x 设为队尾，否则返回 false
    virtual bool EnQueue(DataType x) = 0;

    // 若队列非空，删除队头元素并用 x 返回，否则返回 false
    virtual bool DeQueue(DataType& x) = 0;

    // 若队列非空，用 x 返回队头元素，否则返回 false
    virtual bool getHead(DataType& x) = 0;

    // 队列判空
    virtual bool isEmpty() = 0;

    // 队列判满
    virtual bool isFull() = 0;

    // 返回队列当前元素数量
    virtual int getSize() = 0;

    // 打印元素
    virtual string toString() = 0;
};

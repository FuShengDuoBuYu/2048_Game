#include <string>
using std::string;

typedef int DataType;

/**
 * 栈接口
 */
class IStack {
public:
    virtual ~IStack(){};

    // 若栈未满，将 x 入栈，否则返回 false
    virtual bool push(DataType x) = 0;

    // 若栈非空，弹出栈顶，并用 x 返回，否则返回 false
    virtual bool pop(DataType& x) = 0;

    // 若栈非空，用 x 返回栈顶，否则返回 false
    virtual bool top(DataType& x) = 0;

    // 判空
    virtual bool isEmpty() = 0;

    // 栈当前大小
    virtual int getSize() = 0;

    // 打印元素
    virtual string toString() = 0;
};

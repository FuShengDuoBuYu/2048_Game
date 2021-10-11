# include "IQueue.cpp"
using namespace std;

/**
 * 使用数组实现顺序队列
 */
class SeqQueue:public IQueue{
private:
    DataType* data;     // 存放队列元素的数组
    int front, rear;    // 队尾与队头指针
    int maxSize;        // data数组大小

public:
    SeqQueue(int cap){
        this->maxSize = cap;
        //分配一个cap大小的int类型数组
        data = (DataType *)malloc((maxSize+1) * sizeof(int));
        //将头指针和尾指针都设置为0
        rear = front = 0;
    }

    ~SeqQueue(){

    }

    bool EnQueue(DataType x) {
        //如果满了就return
        if(isFull())
            return false;
        else{
            //如果没满就插入到队尾
            data[rear%(maxSize+1)] = x;
            rear++;
            return true;
        }
    }

    bool DeQueue(DataType& x) {
        if(!isEmpty()){
            x = data[front % (maxSize+1)];
            front++;
            return true;
        }
        else{
            return false;
        }
    }

    bool getHead(DataType& x) {
        if(!isEmpty()){
            x = data[front%(maxSize+1)];
            return true;
        }
        else{
            return false;
        }
    }

    bool isEmpty() {
        return front%(maxSize+1) == rear%(maxSize+1);
    }

    bool isFull(){
        return (rear+1)% (maxSize+1) == front%(maxSize+1);
    }

    int getSize(){
        return (rear - front) % (maxSize+1);
    }

    string toString(){
        string res;
        for(int i = front; i < front + getSize(); i++){
            res += to_string(data[i % (maxSize+1)]) + " ";
        }
        return res;
    }
};
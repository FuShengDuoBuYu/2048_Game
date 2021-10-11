#include "IStack.cpp"
#include "SeqQueue.cpp"

/**
 * 用两个队列实现栈
 */
class MyStack:public IStack{
private:
    IQueue* queue1 = nullptr;
    IQueue* queue2 = nullptr;

public:
    // 此函数不需要修改 (本次不用考虑两个队列的初始容量)
    MyStack(){
        queue1 = new SeqQueue(5);
        queue2 = new SeqQueue(5);
    }

    bool push(DataType x){
        if(queue1->isFull())
            return false;
        else{
            queue1->EnQueue(x);
            return true;
        }
    }

    bool pop(DataType& x) {
        if(queue1->isEmpty())
            return false;
        else{
            int data;
            //将除了最顶的一个元素都复制到queue2中
            for (int i = 0; i < queue1->getSize()-1;i++){
                queue1->DeQueue(data);
                queue2->EnQueue(data);
            }
            //去掉顶元素
            queue1->DeQueue(x);
            //清空缓存队列中的数据
            while(!queue1->isEmpty()){
                queue1->DeQueue(data);
            }
            //将数值复制回去
            IQueue *tempQueue = nullptr;
            tempQueue = queue1;
            queue1 = queue2;
            queue2 = tempQueue;
            return true;
        }
    }

    bool top(DataType& x){
        if(queue1->isEmpty())
            return false;
        else{
            int data;
            //将除了最顶的一个元素都复制到queue2中
            for (int i = 0; i < queue1->getSize()-1;i++){
                queue1->DeQueue(data);
                queue2->EnQueue(data);
            }
            //获取顶元素
            queue1->getHead(x);
            //清空缓存队列中的数据
            while(!queue1->isEmpty()){
                queue1->DeQueue(data);
            }
            //将数值复制回去
            queue2->EnQueue(x);
            IQueue *tempQueue = nullptr;
            tempQueue = queue1;
            queue1 = queue2;
            queue2 = tempQueue;
            return true;
        }
    }

    bool isEmpty(){
        return queue1->isEmpty();
    }

    int getSize(){
        return queue1->getSize();
    }

    string toString(){
        return queue1->toString();
    }
};
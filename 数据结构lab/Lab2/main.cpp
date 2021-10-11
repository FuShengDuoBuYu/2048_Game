/**
 * 自测用例
 */

#include "MyStack.cpp"
#include <cassert>
#include <iostream>

using namespace std;

void printQueue(SeqQueue& queue){
    cout << "queue: " << queue.toString() << "  size:" << queue.getSize() << endl;
}
void printStack(MyStack& stack){
    cout << "stack: " << stack.toString() << "  size:" << stack.getSize() << endl;
}

void testQueue(){
    SeqQueue queue(5);

    printQueue(queue);  // queue:   size:0
    assert(queue.isEmpty());

    int testHead;
    assert(queue.EnQueue(1));
    assert(queue.EnQueue(2));
    assert(queue.getHead(testHead));
    assert(testHead == 1);
    printQueue(queue);  // queue: 1 2   size:2

    assert(queue.EnQueue(3));
    assert(queue.EnQueue(4));
    assert(queue.EnQueue(5));
    printQueue(queue);  // queue: 1 2 3 4 5   size:5

    assert(!queue.EnQueue(6));
    printQueue(queue);  // queue: 1 2 3 4 5   size:5

    int res;
    assert(queue.DeQueue(res));
    assert(res == 1);
    assert(queue.EnQueue(6));
    printQueue(queue);  // queue: 2 3 4 5 6   size:5

}

void testStack() {
    MyStack stack;
    assert(stack.isEmpty());
    assert(stack.push(1));
    assert(stack.push(2));
    printStack(stack); // stack: 1 2   size:2

    int top;
    assert(stack.top(top));
    assert(top == 2);
    printStack(stack); // stack: 1 2   size:2

    int res;
    assert(stack.pop(res));
    assert(res == 2);
    assert(stack.push(3));
    printStack(stack);  // stack: 1 3   size:2

    assert(stack.pop(res));
    assert(stack.pop(res));
    assert(!stack.pop(res));
    printStack(stack); // stack:   size:0

}

int main(){
    cout << "\n ===== Queue Test Cases ===== " << endl;
    testQueue();

    cout << "\n ===== Stack Test Cases ===== " << endl;
    testStack();
}
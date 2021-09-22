#include "Term.cpp"
#include <iostream>
using namespace std;

class Polynomial {

private:

    Term *head = nullptr;

public:

    Polynomial(Term *head) : head(head) {}

    // get the first term
    Term* getFirst() {
        return head;
    }

    // set the first term
    void setFirst(Term *first) {
        head = first;
    }

    // add a single term to the polynomial
    void addTerm(Term *term) {
        //先判断添加的term是否为空
        if(term==nullptr){

        }else{
            //如果此时链表头为空,就先将头赋值
            if(head==nullptr){
                head = term;
            }
            //若头不为空,就将这个项先放到后面
            else{
                //todo:进行多项式合并
                Term *t = head;
                while(t->getNext()!=nullptr){
                    t = t->getNext();
                }
                t->setNext(term);
                t = t->getNext();
            }
        }
        
    }

    // add another polynomial, and return the sum
    Polynomial add(Polynomial *another) {
        Term *copyHead = head;
        Term *anotherHead = another->head;
        //新创建 一个链表
        Polynomial *result = new Polynomial(head);
        while(anotherHead!=nullptr){
            result->addTerm(new Term(anotherHead->getCoef(),anotherHead->getExp()));
            anotherHead = anotherHead->getNext();
        }
        return *result;
    }

    // convert to string representation
    string toString() {
        string result = "";
        Term *t;
        t = sortLink(head);
        while(t!=nullptr){
            string sign = "";
            if(t->getCoef()>0){
                if(t->getNext()!=nullptr)
                    sign = "+";
            }if(t->getNext()!=nullptr&&t->getNext()->getCoef()<0){
                sign = "";
            }
            if(t->getNext()!=nullptr&&t->getNext()->getCoef()>0){
                sign = "+";
            }
            if(t->getCoef()<0)
            result.append((t->getCoef()==-1?"-":to_string(t->getCoef()))).append("x^").append(to_string(t->getExp())).append(sign);
            if(t->getCoef()>0)
            result.append((t->getCoef()==1?"":to_string(t->getCoef()))).append("x^").append(to_string(t->getExp())).append(sign);
            t = t->getNext();
        }
        return result;
    }

    Term* sortLink(Term* head){
        Term *sortedHead,*tempHead =  head;
        //初始化一个长度为原长度的链表
        Term t = Term(0, 0);
        sortedHead = &t;
        Term *tempSortedHead = sortedHead;
        int length = 1;
        while(tempHead->getNext()!=nullptr){
            Term *t1 = new Term(0, 0);
            tempSortedHead->setNext(t1);
            tempSortedHead = tempSortedHead->getNext();
            tempHead = tempHead->getNext();
            length++;
        }
        tempHead = head;
        tempSortedHead = sortedHead;

        //根据指数大小从大到小排序
        int exps[length];
        for (int i = 0; i < length;i++){
            //先将指数取出来放到数组里
            exps[i] = tempHead->getExp();
            tempHead = tempHead->getNext();
        }
        tempHead = head;
            //对指数排序
        for (int i = 0; i < length;i++){
            for (int j = i + 1; j < length;j++){
                if(exps[i]<=exps[j]){
                    int temp = exps[j];
                    exps[j] = exps[i];
                    exps[i] = temp;
                }
            }
        }

        //根据指数的序进行查找对应的系数
        bool inserted = false;
        for (int i = 0; i < length;i++){
            while(tempHead!=nullptr){
                if(tempHead->getExp()==exps[i]){
                    //如果有相同的指数,需要合并同类项
                    if(i<length-1&&exps[i]==exps[i+1]){
                        //找出所有指数为该值的一块合并
                        Term *tempTempHead = tempHead;
                        while(tempTempHead!=nullptr){
                            if(tempTempHead->getExp()==exps[i]){
                                tempSortedHead->setCoef(tempTempHead->getCoef()+tempSortedHead->getCoef());
                                tempSortedHead->setExp(tempTempHead->getExp());
                            }
                            tempTempHead = tempTempHead->getNext();
                        }
                        while(exps[i]==exps[i+1]){
                            i++;
                        }
                        break;
                    }else{
                        tempSortedHead->setCoef(tempHead->getCoef());
                        tempSortedHead->setExp(tempHead->getExp());
                    }
                }
                tempHead = tempHead->getNext();
            }
            tempSortedHead = tempSortedHead->getNext();
            tempHead = head;
        }
        tempHead = head;

        //将排序后的赋值给head
        while(tempHead!=nullptr){
            tempHead->setExp(sortedHead->getExp());
            tempHead->setCoef(sortedHead->getCoef());
            tempHead = tempHead->getNext();
            sortedHead = sortedHead->getNext();
        }
        tempHead = head;

        //将head中的系数为0的项删除
        //如果头是系数为0
        if(tempHead->getCoef() == 0){
            head = tempHead->getNext();
            tempHead = head;
        }
        //如果是在非头处系数为0
        
        while(tempHead->getNext()!=nullptr){
            if(tempHead->getNext()->getCoef()==0){
                tempHead->setNext(tempHead->getNext()->getNext());
            }else{
                tempHead = tempHead->getNext();
            }
        }
        
        return head;
    }
};


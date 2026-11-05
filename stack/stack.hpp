#pragma once
#include "array.hpp"
#include "list.hpp"

template <typename T>
class AStack:public Array<T>{
    public:
        void push(T value){this->push_back(value);}
        T pop(){return this->pop_back();}
        T peek(){
            return this->size==0 ? throw EmptyDataException() : this->data[this->size-1];
        }
        bool isEmpty(){return this->size == 0;}
};

template <typename T>
class LStack:public List<T>{
    public:
        void push(T value){this->push_back(value);}
        T pop(){return this->pop_back();}
        T peek(){
            return this->end == nullptr ? throw EmptyDataException() : this->end->value;
        }
        bool isEmpty(){return this->head == nullptr;}
};

template <typename T, template<typename> class Stack>
class Limitedstack : public Stack<T>{
    private: int limit;
    public:
        Limitedstack(int max){
            if (max<=0) throw NegativeSizeException();
            limit = max;
        }

        virtual void push(T value){
            if (this->getsize()>=limit) throw OverflowDataException();
            Stack<T>::push(value);
        }

        friend istream& operator>> (istream& in,  Limitedstack& ls){
            int n; in>>n; int f=0;
            if(n<0) throw NegativeSizeException();
            if (n>ls.limit-ls.size){
                f = 1; n = ls.limit-ls.size;
            }
            for (int i=0; i<n;i++){
                T value; in>>value;
                ls.push(value);
            }
            if (f==1) throw StackOverflowException();
            return in;
        }
};

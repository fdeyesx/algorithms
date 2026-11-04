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


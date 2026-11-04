#pragma once
#include <iostream>
#include "errors.hpp"
using namespace std;

template <typename T>
class Array{
    protected:
        int size = 0; int capacity = 10; T *data;
    public:
        Array(){data = new T[capacity];}
        virtual ~Array(){delete[] data;}

        Array(const Array& arr){
            size = arr.size;
            capacity = arr.capacity;
            data = new T[capacity];
            for (int i = 0;i<size;i++) data[i] = arr.data[i];
        }

        T& operator[](int index){
            if (index<0 || index >= size) throw OverflowDataException();
            return data[index];
        }

        const Array& operator= (const Array& arr){
            if (this==&arr) throw SameDataException();

            T *newdata = new T[arr.capacity];
            for (int i = 0;i<arr.size;i++) newdata[i] = arr.data[i];
            delete[] data;
            
            data = newdata;
            size = arr.size;
            capacity = arr.capacity;
            
            return *this;
        }

        T pop_back(){
            return size == 0 ? throw EmptyDataException() : data[--size];
        }

        T pop_front(){
            if (size==0) throw EmptyDataException();
            T val = data[0];
            for (int i = 0; i<size; i++) data[i] = data[i+1];
            size--;
        }

        friend ostream& operator<< (ostream& out, Array& arr){
            for (int i = 0; i<arr.size; ++i){
                out<<arr.data[i];
                if (i+1<arr.size) out<<" ";
            }
            return out;
        }

        virtual void push_back(T value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        virtual void push_front(T value){
            if (size==capacity) resize();
            for (int i = size; i > 0; --i) data[i] = data[i-1];
            data[0] = value; size++;
        }

        friend istream& operator>> (istream& in, Array& arr){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
                for (int i=0; i<n;i++){
                    T value; in>>value;
                    arr.push_back(value);
                }
                return in;
        }

        void clear(){
            size = 0;
        }
    private:
        void resize(){
            capacity*=2;
            T *tmp = new T[capacity];
            for (int i =0; i<size;i++) tmp[i] = data[i];
            delete[] data; data = tmp;
        }
};
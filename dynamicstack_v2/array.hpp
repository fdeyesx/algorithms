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
            data = T int[capacity];
            for (int i = 0;i<size;i++) data[i] = arr.data[i];
        }

        int& operator[](int index){
            if (index<0 || index >= size) throw OverflowDataException();
            return data[index];
        }

        const Array& operator= (const Array& arr){
            if (this==&arr) throw SameDataException();

            T *newdata = new T[arr.capacity];
            for (int i = 0;i<size;i++) newdata[i] = arr.data[i];
            delete[] data;
            
            data = newdata;
            size = arr.size;
            capacity = arr.capacity;
            
            return *this;
        }

        int pop(){
            return size == 0 ? throw EmptyArrayException() : data[--size];
        }

        friend ostream& operator<< (ostream& out, Array& arr){
            for (int i = 0; i<arr.size; ++i){
                out<<arr.data[i];
                if (i+1<arr.size) out<<" ";
            }
            return out;
        }

        virtual void push(int value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        friend istream& operator>> (istream& in, Array& arr){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
                for (int i=0; i<n;i++){
                    int value; in>>value;
                    arr.push(value);
                }
                return in;
        }

        void change(int index){
            if (index<0 || index >= size) throw OverflowDataException();
            int value; cin>>value; data[index] = value;
        }

        void clear(){
            size = 0;
        }

        int search(int value){
            for (int i = 0; i<size;i++){
                if (data[i] == value) return i;
            }
            throw NotFound();
        }
    private:
        void resize(){
            capacity*=2;
            int *tmp = new int[capacity];
            for (int i =0; i<size;i++) tmp[i] = data[i];
            delete[] data; data = tmp;
        }
};

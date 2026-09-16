#include <iostream>
using namespace std;

class Array{
    public:
        int size = 0; int capacity = 10; int *data;
        Array(){data = new int[capacity];}
        ~Array(){delete[] data;}

        void push(){
            if(size==capacity) resize();
            int value; cin >> value;
            data[size++] = value;
        }

        int pop(){
            return size == 0 ? -1 : data[--size];
        }

        void print(){
            int index; cin>>index; 
            if (index>=0 && index<size) cout << data[index] << "\n";
        }

        void change(){
            int index; cin>>index; int value; cin>>value;
            if (index>=0 && index<size) data[index] = value;
        }

        void clear(){
            size = 0;
        }

        int search(){
            int value; cin>>value;
            for (int i = 0; i<size;i++){
                if (data[i] == value) return i;
            }
            return -1;
        }
    private:
        void resize(){
            capacity*=2;
            int *tmp = new int[capacity];
            for (int i =0; i<size;i++) tmp[i] = data[i];
            delete[] data; data = tmp;
        }
};

int main(){
    Array arr; 
    int command; cin>>command;
    while(command){
        switch(command){
            case 1: arr.push(); break;
            case 2: cout << arr.pop() << "\n"; break;
            case 3: arr.print(); break;
            case 4: arr.change(); break;
            case 5: cout << arr.search() << "\n"; break;
            case 6: arr.clear(); break;
        }
        cin>>command;
    }
    return 0;
}

#include <iostream>
using namespace std;

class Array{
    public:
        int size = 0; int capacity = 10; int *data;
        Array(){data = new int[capacity];}
        ~Array(){delete[] data;}

        Array(const Array& arr){
            size = arr.size;
            capacity = arr.capacity;
            data = new int[capacity];
            for (int i = 0;i<size;i++){
                data[i] = arr.data[i];
            }
        }

        int& operator[](int index){ return data[index];}

        const Array& operator= (const Array& arr){
            if (this==&arr) return *this;
            delete[] data;
            
            size = arr.size;
            capacity = arr.capacity;
            data = new int[capacity];
            for (int i = 0;i<size;i++){
                data[i] = arr.data[i];
            }

            return *this;
        }

        int pop(){
            return size == 0 ? -1 : data[--size];
        }

        friend ostream& operator<< (ostream& out, Array& arr){
            for (int i = 0; i<arr.size; ++i){
                out<<arr.data[i];
                if (i+1<arr.size) out<<" ";
            }
            return out;
        }

        void push(int value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        friend istream& operator>> (istream& in,  Array& arr){
            int n; in>>n;
            arr.clear();
            for (int i=0; i<n;i++){
                int value; in>>value;
                arr.push(value);
            }
            return in;
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
            case 1:{int value; cin>>value; arr.push(value); break;}
            case 2: cout << arr.pop() << "\n"; break;
            case 3: cout<<arr<<"\n"; break;
            case 4: arr.change(); break;
            case 5: cout << arr.search() << "\n"; break;
            case 6: arr.clear(); break;
            case 7: cin>>arr; break;
        }
        cin>>command;
    }
    return 0;
}

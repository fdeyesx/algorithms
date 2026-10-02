#include <iostream>
#include <cassert>
using namespace std;

class arrayerror{
    protected: string message; 
    public:
        arrayerror(const string& text) {message = text;}
        ~arrayerror() {}
        string msg(){return message;}
};

class EmptyArrayException : public arrayerror{
    public:
        EmptyArrayException(): arrayerror("Array is empty."){}
};

class WrongTypeException : public arrayerror{
    public:
        WrongTypeException(): arrayerror("Wrong type's been entered."){}
};

class SameDataException : public arrayerror{
    public:
        SameDataException(): arrayerror("Assignment same array."){}
};

class OverflowDataException : public arrayerror{
    public:
        OverflowDataException(): arrayerror("Index's out of range."){}
};

class NegativeSizeException : public arrayerror{
    public:
        NegativeSizeException(): arrayerror("Negative number for size has been entered."){}
};

class NotFound : public arrayerror{
    public:
        NotFound(): arrayerror("Value hasn't been found."){}
};

class Array{
    public:
        int size = 0; int capacity = 10; int *data;
        Array(){data = new int[capacity];}
        ~Array(){delete[] data;}

        Array(const Array& arr){
            size = arr.size;
            capacity = arr.capacity;
            data = new int[capacity];
            for (int i = 0;i<size;i++) data[i] = arr.data[i];
        }

        int& operator[](int index){
            if (index<0 || index >= size) throw OverflowDataException();
            return data[index];
        }

        const Array& operator= (const Array& arr){
            if (this==&arr) throw SameDataException();

            int *newdata = new int[arr.capacity];
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

        void push(int value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        friend istream& operator>> (istream& in,  Array& arr){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
            else{
                arr.clear();
                for (int i=0; i<n;i++){
                    int value; in>>value;
                    arr.push(value);
                }
                return in;
            }
        }

        void change(int index){
            if (index<0 || index >= size) throw OverflowDataException();
            else {
                int value; cin>>value;
                if (index>=0 && index<size) data[index] = value;
            }
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

void cycle(Array &arr){
    int command; cin>>command;
    while(command){
        switch(command){
            case 1:{
                int value; cin>>value; 
                arr.push(value); 
                break;
            }
            case 2: {
                try{arr.pop();}
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 3: cout<<arr<<"\n"; break;
            case 4: {
                int index; cin>>index;
                try{arr.change(index);}
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 5: {
                int value; cin>>value;
                try{cout<<arr.search(value)<< '\n';}
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 6: arr.clear(); break;
            case 7: {
                try{cin>>arr;}
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
                break;
            }
        }
        cin>>command;
    }
}

void tests(Array &arr){
    string message = " ";

    cout << "1st test - ";
    try{arr.pop();}
    catch(arrayerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    cout << "fine\n";

    cout << "2nd test - ";
    try{arr=arr;}
    catch(arrayerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    cout << "fine\n";

    cout << "3rd test - ";
    arr.push(2); arr.push(18); arr.push(37); arr.push(0);
    try{arr.change(4);}
    catch(arrayerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    
    try{arr.search(15);}
    catch(arrayerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";

    assert(arr.pop() == 0);
    assert(arr.search(18) == 1);
    cout << "fine\n";
}

int main(){
    Array arr; 
    int mode; cout << "Enter <1> for regular use, <2> for tests.\n"; cin >> mode;
    switch (mode){
    case 1:
        cycle(arr);
        break;
    case 2:
        tests(arr);
        break;
    }
    return 0;
}

#include "errors.hpp"
#include "array.hpp"
#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Stack : protected Array<T>{
    public:
        void push(T value){this->Array<T>::push(value);}
        T pop(){return this->Array<T>::pop();}
        void clear(){this->Array<T>::clear();}
        void change(int index) { this->Array<T>::change(index); }
        int search(T value){return this->Array<T>::search(value);}

        T peek(){
            return this->size == 0 ? throw EmptyArrayException() : this->data[this->size-1];
        }

        bool isEmpty(){
            return this->size == 0;
        }

        friend ostream& operator<< (ostream& out, Stack& st){
            for (int i = 0; i<st.size; ++i){
                out<<st.data[i];
                if (i+1<st.size) out<<" ";
            }
            return out;
        }

        friend istream& operator>> (istream& in, Stack& st){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
                for (int i=0; i<n;i++){
                    T value; in>>value;
                    st.push(value);
                }
                return in;
        }
};

template <typename T>
class Limitedstack : public Stack<T>{
    private: int limit;
    public:
        Limitedstack(int max){
            if (max<=0) throw NegativeSizeException();
            limit = max;
        }

        virtual void push(T value){
            if (this->size>=limit) throw OverflowDataException();
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

template <typename T>
void commands(Stack<T>& arr){
    int command; cin>>command;
    while(command){
        switch(command){
            case 1:{
                try{T value; cin>>value; arr.push(value); }
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
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
                try{int index; cin>>index; arr.change(index);}
                catch(arrayerror &e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 5: {
                try{T value; cin>>value; cout<<arr.search(value)<< '\n';}
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

void cycle(){
    int v; cout << "Enter <1> for Stack, <2> for Limited Stack.\n"; cin>>v;
    switch (v){
    case 1:{
        Stack<int> st; commands(st);
        break;
    }
    case 2:{
        int max; cout<<"Enter the limit\n"; cin>>max;
        try{Limitedstack<int> ls(max); commands(ls);}
        catch(arrayerror &e){
            cout << e.msg() << '\n';
        }
        break;
    }
    }
}

void tests(){
    string message = " ";
    Stack<int> st;
    st.push(2); st.push(6); st.push(7);

    assert(st.peek() == 7);
    assert(st.pop() == 7);
    assert(st.peek() == 6);
    assert(!st.isEmpty());
    st.clear(); assert(st.isEmpty());

    Limitedstack<double> ls(4);
    ls.push(45.5); ls.push(8.8); ls.push(14.3); ls.push(25.7);

    try{ls.push(0.0);}
    catch(arrayerror& e){message=e.msg();}
    assert(message != " "); message = " ";

    ls.pop(); ls.push(0.0);
    assert(ls.peek()==0.0);

    Stack<char> letters;
    letters.push('q'); letters.push('e'); letters.push('d');

    assert(letters.pop() == 'd'); assert(letters.pop() == 'e');
    assert(letters.peek() == 'q');

    cout<<"All tests were passed.\n";
}

int main(){
    int mode; cout << "Enter <1> for regular use, <2> for tests.\n"; cin >> mode;
    switch (mode){
    case 1:
        cycle();
        break;
    case 2:
        tests();
        break;
    }
    return 0;
}

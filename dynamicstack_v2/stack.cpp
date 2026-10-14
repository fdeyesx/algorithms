#include "errors.hpp"
#include "array.hpp"
#include <iostream>
#include <cassert>

using namespace std;

class Stack : protected Array{
    public:
        void push(int value){Array::push(value);}
        int pop(){return Array::pop();}
        void clear(){Array::clear();}
        void change(int index) { Array::change(index); }
        int search(int value){return Array::search(value);}

        int peek(){
            return size == 0 ? throw EmptyArrayException() : data[size-1];
        }

        bool isEmpty(){
            return size == 0;
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
                    int value; in>>value;
                    st.push(value);
                }
                return in;
        }
};

class Limitedstack : public Stack{
    private: int limit;
    public:
        Limitedstack(int max){
            if (max<=0) throw NegativeSizeException();
            limit = max;
        }

        virtual void push(int value){
            if (size>=limit) throw OverflowDataException();
            Stack::push(value);
        }

        friend istream& operator>> (istream& in,  Limitedstack& ls){
            int n; in>>n; int f=0;
            if(n<0) throw NegativeSizeException();
            if (n>ls.limit-ls.size){
                f = 1; n = ls.limit-ls.size;
            }
            for (int i=0; i<n;i++){
                int value; in>>value;
                ls.push(value);
            }
            if (f==1) throw StackOverflowException();
            return in;
        }
};

void commands(Stack &arr){
    int command; cin>>command;
    while(command){
        switch(command){
            case 1:{
                try{int value; cin>>value; arr.push(value); }
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
                try{int value; cin>>value; cout<<arr.search(value)<< '\n';}
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
        Stack st; commands(st);
        break;
    }
    case 2:{
        int max; cout<<"Enter the limit\n"; cin>>max;
        try{Limitedstack ls(max); commands(ls);}
        catch(arrayerror &e){
            cout << e.msg() << '\n';
        }
        break;
    }
    }
}

void tests(){
    Stack st; string message = " ";
    st.push(2); st.push(6); st.push(7);

    assert(st.peek() == 7);
    assert(st.pop() == 7);
    assert(st.peek() == 6);
    assert(!st.isEmpty());
    st.clear(); assert(st.isEmpty());

    try{st.peek();}
    catch(arrayerror& e){message=e.msg();}
    assert(message != " "); message = " ";

    Limitedstack ls(4);
    ls.push(45); ls.push(8); ls.push(14); ls.push(25);

    try{ls.push(0);}
    catch(arrayerror& e){message=e.msg();}
    assert(message != " "); message = " ";

    ls.pop(); ls.push(0);
    assert(ls.peek()==0);

    try{Limitedstack ls2(0);}
    catch(arrayerror& e){message=e.msg();}
    assert(message != " "); message = " ";

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
#include "errors.hpp"
#include "array.hpp"
#include <iostream>
#include <cassert>

using namespace std;

class Stack : public Array{
    public: 
        int peek(){
            return size == 0 ? throw EmptyArrayException() : data[size-1];
        }

        bool isEmpty(){
            return size == 0;
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
};

void commands(Array &arr){
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
    int v; cout << "Enter <1> for Array, <2> for Stack, <3> for Limited Stack.\n"; cin>>v;
    switch (v){
    case 1:{
        Array arr; commands(arr);
        break;
    }
    case 2:{
        Stack st; commands(st);
        break;
    }
    case 3:{
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
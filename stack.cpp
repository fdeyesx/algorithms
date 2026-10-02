#include <iostream>
#include <cassert>
using namespace std;

class stackerror{
    protected: string message; 
    public:
        stackerror(const string& text) {message = text;}
        ~stackerror() {}
        string msg(){return message;}
};

class EmptyStackException : public stackerror{
    public:
        EmptyStackException(): stackerror("Stack is empty."){}
};

class WrongTypeException : public stackerror{
    public:
        WrongTypeException(): stackerror("Wrong type's been entered."){}
};

class SameDataException : public stackerror{
    public:
        SameDataException(): stackerror("Assignment same stack."){}
};

class IntStack {
    private:
        struct Node {
            int value;
            Node* next;
        };
        Node* top;

    public:
        IntStack() {top = nullptr;}
        ~IntStack() {
            while (top != nullptr) {
                Node* tmp = top;
                top = top->next;
                delete tmp;
            }
        }

        IntStack(const IntStack& stack){
            if (stack.top == nullptr) throw EmptyStackException();

            top = new Node;
            top->value=stack.top->value;
            top->next=nullptr;

            Node*tmp = top; Node*copy = stack.top->next;
            while(copy!=nullptr){
                Node*node = new Node;
                node->value=copy->value;
                node->next=nullptr;

                tmp->next=node;
                tmp=node;
                copy=copy->next;
            }
        }

        const IntStack& operator= (const IntStack& stack){
            if(this == &stack) throw SameDataException();

            IntStack tmp(stack); clear();
            top = tmp.top;
            tmp.top=nullptr;

            return *this;
        }
        
        friend ostream& operator<< (ostream& out, IntStack& stack){
            Node* cur = stack.top;
            while (cur != nullptr) {
                out << cur->value << " -> ";
                cur = cur->next;
            }
            out << "NULL\n";
            return out;
        }

        void push(int value) {
            Node* node = new Node;
            node->value = value;
            node->next = top;
            top = node;
        }

        friend istream& operator>> (istream& in,  IntStack& stack){
            int n; in>>n;
            stack.clear();
            for (int i=0; i<n;i++){
                int value; in>>value;
                stack.push(value);
            }
            return in;
        }

        int pop() {
            if (top == nullptr) throw EmptyStackException();
            int value = top->value;
            Node* tmp = top;
            top = top->next;
            delete tmp;
            return value;
        }

        int peek() {
            return top == nullptr ? throw EmptyStackException() : top->value;
        }

        bool isEmpty() {
            return top == nullptr;
        }

        void clear() {
            while (top != nullptr) {
                Node* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
};

void cycle(IntStack &st){
    int command;
    cin >> command;
    while (command) {
        switch (command) {
            case 1: {
                int value; cin >> value; 
                st.push(value); 
                break;
            }
            case 2: {
                try{st.pop();}
                catch(stackerror& e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 3: cout << st; break;
            case 4: {
                try{st.peek();}
                catch(stackerror& e){
                    cout << e.msg() << '\n';
                }
                break;
            }
            case 5: cout << st.isEmpty() << "\n"; break;
            case 6: st.clear(); break;
            case 7: cin >> st; break;
        }
        cin >> command;
    }
}

void tests(IntStack &st){
    string message = " ";

    cout << "1st test - ";
    try{st.pop();}
    catch(stackerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    cout << "fine\n";

    cout << "2nd test - ";
    try{st.peek();}
    catch(stackerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    cout << "fine\n";

    cout << "3rd test - ";
    st.push(2); st.push(6); st.push(7);
    try{st=st;}
    catch(stackerror& e){
        message = e.msg();
    }
    assert(message != " "); message = " ";
    st.clear();
    cout << "fine\n";

    cout << "4th test - ";
    st.push(10); st.push(20); st.push(7); 
    assert(st.peek() == 7);
    assert(st.pop() == 7);
    assert(st.peek() == 20);
    assert(st.isEmpty() == 0);
    cout << "fine\n";
}

int main() {
    IntStack st;
    int mode; cout << "Enter <1> for regular use, <2> for tests.\n"; cin >> mode;
    switch (mode){
    case 1:
        cycle(st);
        break;
    case 2:
        tests(st);
        break;
    }
    return 0;
}

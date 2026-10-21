#include <iostream>
#include <sstream>
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

class Printable {
public:
    virtual ~Printable() = default;
    virtual void print(ostream& os) const = 0;
};

class Cloneable {
public:
    virtual ~Cloneable() = default;
    virtual Cloneable* clone() const = 0;
};

ostream& operator << (ostream& os, const Printable& p){
    p.print(os);
    return os;
};

class IntStack: public Printable, public Cloneable{
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

        void print(ostream& os) const override{
            Node* cur = top;
            while (cur != nullptr) {
                os << cur->value << " -> ";
                cur = cur->next;
            }
            os << "NULL\n";
        }

        IntStack* clone() const override{
            return new IntStack(*this);
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
    st.push(6); st.push(123); st.push(92);
    ostringstream stroke;
    stroke<<st;
    assert(stroke.str() == "92 -> 123 -> 6 -> NULL\n");

    IntStack *copy = st.clone();
    assert(copy != nullptr);
    assert(copy != &st);

    ostringstream stroke2;
    stroke2<<*copy;
    assert(stroke2.str() == "92 -> 123 -> 6 -> NULL\n");

    copy->pop();
    assert(st.peek() == 92);
    assert(copy->peek() == 123);

    delete copy;
    cout << "All tests were passed.\n";
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

#include <iostream>
using namespace std;

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
            if (stack.top == nullptr) return;

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
            if (top == nullptr) return -1;
            int value = top->value;
            Node* tmp = top;
            top = top->next;
            delete tmp;
            return value;
        }

        int peek() {
            return top == nullptr ? -1 : top->value;
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

int main() {
    IntStack st;
    int command;
    cin >> command;
    while (command) {
        switch (command) {
            case 1: {int value; cin >> value; st.push(value); break;}
            case 2: cout << st.pop() << "\n"; break;
            case 3: cout << st; break;
            case 4: cout << st.peek() << "\n"; break;
            case 5: cout << st.isEmpty() << "\n"; break;
            case 6: st.clear(); break;
            case 7: cin >> st; break;
        }
        cin >> command;
    }
    return 0;
}

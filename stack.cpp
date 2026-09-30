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
        IntStack(){Node* top = nullptr;}
        ~IntStack(){
            while (top != nullptr) {
                Node* tmp = top;
                top = top->next;
                delete tmp;
            }
        }

        void push(int value){
            Node* node = new Node;
            node->value = value;
            node->next = top;
            top = node;
        }

        int pop(){
            if (top == nullptr) return -1;
            int value = top->value;
            Node* tmp = top;
            top = top->next;
            delete tmp;
            return value;
        }

        int peek(){
            return top == nullptr ? -1 : top->value;
        }

        bool isEmpty(){
            return top == nullptr;
        }

        void print(){
            Node* cur = top;
            while (cur != nullptr) {
                cout << cur->value << " -> ";
                cur = cur->next;
            }
            cout << "NULL\n";
        }

        void clear(){
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
            case 1: int value; cin >> value; st.push(value); break;
            case 2: cout << st.pop() << "\n"; break;
            case 3: st.print(); break;
            case 4: cout << st.peek() << "\n"; break;
            case 5: cout << st.isEmpty() << "\n"; break;
            case 6: st.clear(); break;
        }
        cin >> command;
    }
    return 0;
}

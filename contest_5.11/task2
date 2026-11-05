#include <iostream>
using namespace std;

class errors{
    protected: std::string message; 
    public:
        errors(const std::string& text) {message = text;}
        virtual ~errors() {}
        std::string msg(){return message;}
};

class EmptyDataException : public errors{
    public:
        EmptyDataException(): errors("Data is empty."){}
};

class WrongTypeException : public errors{
    public:
        WrongTypeException(): errors("Wrong type's been entered."){}
};

class SameDataException : public errors{
    public:
        SameDataException(): errors("Assignment same data."){}
};

class OverflowDataException : public errors{
    public:
        OverflowDataException(): errors("Index's out of range."){}
};

class NegativeSizeException : public errors{
    public:
        NegativeSizeException(): errors("Negative number for size has been entered."){}
};

class NotFound : public errors{
    public:
        NotFound(): errors("Value hasn't been found."){}
};

class OverflowException : public errors {
    public:
        OverflowException() : errors("Limit's been reached.") {}
};

class List{
    protected:
        struct Node {
            int value;
            Node* next; Node* prev;
        };
        Node* head; Node* end; int count;

    public:
        List(){head = nullptr; end = nullptr; count = 0;}
        virtual ~List(){clear();}

        List(const List& list){
            if (list.head == nullptr) throw EmptyDataException();
            head = nullptr; end = nullptr;
            Node*copy = list.head;
            while(copy!=nullptr){
                push_back(copy->value);
                copy = copy->next;
            }
        }

        const List& operator= (const List& list){
            if(this == &list) throw SameDataException();

            List tmp(list); clear();
            head = tmp.head;
            end = tmp.end;
            tmp.head=nullptr;
            tmp.end = nullptr;
            return *this;
        }

        void push_front(int value) {
            Node* node = new Node;
            node->value = value;
            node->prev = nullptr;
            node->next = head;

            if (head != nullptr) head->prev = node;
            else end = node;
            head = node;
            count++;
        }

        void push_back(int value) {
            Node* node = new Node;
            node->value = value;
            node->prev = end;
            node->next = nullptr;

            if (end != nullptr) end->next = node;
            else head = node;
            end = node;
            count++;
        }

        friend istream& operator>> (istream& in,  List& list){
            int n; in>>n;
            list.clear();
            for (int i=0; i<n;i++){
                int value; in>>value;
                list.push_back(value);
            }
            return in;
        }

        int pop_front() {
            if (head == nullptr) throw EmptyDataException();
            int value = head->value;
            Node* tmp = head;
            head = head->next;
            if(head!=nullptr) head->prev = nullptr;
            else end = nullptr;
            delete tmp; count--;
            return value;
        }
        
        int pop_back() {
            if (end == nullptr) throw EmptyDataException();
            int value = end->value;
            Node* tmp = end;
            end = end->prev;
            if(end!=nullptr) end->next = nullptr;
            else head = nullptr;
            delete tmp; count--;
            return value;
        }

        friend ostream& operator<< (ostream& out, List& list){
            Node* cur = list.head;
            while (cur != nullptr) {
                out << cur->value << " ";
                cur = cur->next;
            }
            out << "\n";
            return out;
        }

        void clear(){
            while (head != nullptr) {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            end = nullptr;
        }
        int getsize(){return count;}

        void sort(){
            if(head!=nullptr) merge_sort(head);
            end=head;
            while(end->next) end = end->next;
        }
    private:
        void merge(Node*left, Node*right, Node*&result){
            if(!left){result = right; return;}; if(!right){result = left; return;};
            if(left->value <= right->value){
                result = left;
                merge(left->next, right,result->next);
                result->next->prev = result;
                result->prev = nullptr;             
            } else {
                result = right;
                merge(left, right->next,result->next);
                result->next->prev = result;
                result->prev = nullptr;
            }
        }

        void merge_sort(Node*&node){
            if(node==nullptr || node->next == nullptr) return;
            int len = 0;
            Node* tmp = node;
            while(tmp){tmp=tmp->next; len++;}
            int middle_index = len/2;

            Node*middle = node; int i=0;
            while (i<middle_index-1){
                middle = middle->next; i++;
            }

            Node*right_list = middle->next;
            middle->next=nullptr;
            if (right_list) right_list->prev=nullptr;
            
            merge_sort(node); merge_sort(right_list); merge(node,right_list,node);
        }
};

int main(){
    List list; cin >> list;
    list.sort();
    cout << list; 
    return 0;
}

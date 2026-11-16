#include <iostream>
#include <iterator>
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

class List; 
struct Node {
    int value; Node* next; Node* prev; };

class Listiterator{
    public:
        Node*current;
        Listiterator(){current = nullptr;}
        ~Listiterator(){}
        int& operator*() const {return current->value;}
        bool operator==(const Listiterator& l2){return current == l2.current;}
        bool operator!=(const Listiterator& l2){return current != l2.current;}
        Listiterator& operator=(const Listiterator& l2){current = l2.current; return *this;}
        Listiterator& operator++(){current=current->next; return *this;}
        Listiterator begin(){Listiterator it; it.current = current; return it;}
        Listiterator end(){return Listiterator();}
        friend class List;
};

class List{
    protected:
        Node* head; Node* end; int count;
    public:
        List(){head = nullptr; end = nullptr; count = 0;}
        virtual ~List(){clear();}

        friend class Listiterator;

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
            if(head!=nullptr){
                merge_sort(head);
                Listiterator it; it.current = head;
                while(it.current != nullptr && it.current->next != nullptr) ++it;
                end = it.current;
            }
        }
    private:
        void merge(Node*left, Node*right, Node*&result){
            if(!left){result = right; return;}; if(!right){result = left; return;};

            Listiterator l_it; l_it.current = left;
            Listiterator r_it; r_it.current = right;

            if(*l_it <= *r_it){
                result = left; ++l_it; 
                Listiterator result_it; result_it.current = result; 
                Node* temp_next = nullptr;
                merge(l_it.current, right, temp_next);
                if (temp_next) {
                    Listiterator tn_it; tn_it.current = temp_next;
                    tn_it.current->prev = result_it.current; 
                }
                result_it.current->prev = nullptr;
                result_it.current->next = temp_next;
            } else {
                result = right; ++r_it; 
                Listiterator result_it; result_it.current = result; 
                Node* temp_next = nullptr;
                merge(left, r_it.current, temp_next);
                if (temp_next) {
                    Listiterator tn_it; tn_it.current = temp_next;
                    tn_it.current->prev = result_it.current; 
                }
                result_it.current->prev = nullptr;
                result_it.current->next = temp_next;
            }
        }

        void merge_sort(Node*&node){
            if(node==nullptr || node->next == nullptr) return;
            int len = 0; Listiterator it;
            for (it.current = node; it.current != nullptr; ++it)len++;

            int middle_index = len/2;
            Listiterator middle; middle.current = node; int i=0;
            while (i<middle_index-1){
                ++middle; i++;
            }
            Node* left_list = node;
            Node* right_list = nullptr;

            Listiterator temp = middle; ++temp;
            Node* temp_next = temp.current;

            middle.current->next = nullptr; 

            Listiterator tn_it; tn_it.current = temp_next;
            tn_it.current->prev = nullptr;
            right_list = tn_it.current;

            merge_sort(left_list); merge_sort(right_list); 
            node = nullptr; merge(left_list,right_list,node);
        }
};

int main(){
    List list; cin >> list;
    list.sort();
    cout << list; 
    return 0;
}

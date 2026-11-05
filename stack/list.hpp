#pragma once
#include <iostream>
#include "errors.hpp"
using namespace std;

#pragma once
#include <iostream>
#include "errors.hpp"
using namespace std;

template <typename T>
class List{
    protected:
        struct Node {
            T value;
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

        void push_front(T value) {
            Node* node = new Node;
            node->value = value;
            node->prev = nullptr;
            node->next = head;

            if (head != nullptr) head->prev = node;
            else end = node;
            head = node;
            count++;
        }

        void push_back(T value) {
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
                T value; in>>value;
                list.push_back(value);
            }
            return in;
        }

        T pop_front() {
            if (head == nullptr) throw EmptyDataException();
            T value = head->value;
            Node* tmp = head;
            head = head->next;
            if(head!=nullptr) head->prev = nullptr;
            else end = nullptr;
            delete tmp; count--;
            return value;
        }
        
        T pop_back() {
            if (end == nullptr) throw EmptyDataException();
            T value = end->value;
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
                out << cur->value << " -> ";
                cur = cur->next;
            }
            out << "NULL\n";
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
        T getsize(){return count;}
};

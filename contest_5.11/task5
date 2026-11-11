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

class Array;
class Arrayiterator{
    public:
        int*current; int size;
        Arrayiterator(){current = nullptr;}
        ~Arrayiterator(){}
        int& operator*() const {return *current;}
        bool operator==(const Arrayiterator& l2){return current == l2.current;}
        bool operator!=(const Arrayiterator& l2){return current != l2.current;}
        Arrayiterator& operator=(const Arrayiterator& l2){current = l2.current; size = l2.size; return *this;}
        Arrayiterator& operator++(){current=current+1; return *this;}
        Arrayiterator begin(){Arrayiterator it; it.current = current; it.size = size; return it;}
        Arrayiterator end(){Arrayiterator it; it.current = current+size; return it;}

        Arrayiterator operator+(int n){Arrayiterator it; it.current = current+n; return it;}
        Arrayiterator operator-(int n){Arrayiterator it; it.current = current-n; return it;}

        int operator-(const Arrayiterator& l2){return current-l2.current;}

        bool operator<(const Arrayiterator& l2){return current<l2.current;}
        bool operator<=(const Arrayiterator& l2){return current<=l2.current;}
        bool operator>(const Arrayiterator& l2){return current>l2.current;}
        bool operator>=(const Arrayiterator& l2){return current>=l2.current;}

        int& operator[](int n){return current[n];}
        friend class Array;
};

class Array{
    protected:
        int size = 0; int capacity = 10; int *data;
    public:
        Array(){data = new int[capacity];}
        virtual ~Array(){delete[] data;}

        Array(const Array& arr){
            size = arr.size;
            capacity = arr.capacity;
            data = new int[capacity];
            for (int i = 0;i<size;i++) data[i] = arr.data[i];
        }

        int& operator[](int index){
            if (index<0 || index >= size) throw OverflowDataException();
            return data[index];
        }

        const Array& operator= (const Array& arr){
            if (this==&arr) throw SameDataException();

            int *newdata = new int[arr.capacity];
            for (int i = 0;i<arr.size;i++) newdata[i] = arr.data[i];
            delete[] data;
            
            data = newdata;
            size = arr.size;
            capacity = arr.capacity;
            
            return *this;
        }

        int pop_back(){
            return size == 0 ? throw EmptyDataException() : data[--size];
        }

        int pop_front(){
            if (size==0) throw EmptyDataException();
            int val = data[0];
            for (int i = 0; i<size; i++) data[i] = data[i+1];
            size--;
        }

        friend ostream& operator<< (ostream& out, Array& arr){
            for (int i = 0; i<arr.size; ++i){
                out<<arr.data[i];
                if (i+1<arr.size) out<<" ";
            }
            return out;
        }

        virtual void push_back(int value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        virtual void push_front(int value){
            if (size==capacity) resize();
            for (int i = size; i > 0; --i) data[i] = data[i-1];
            data[0] = value; size++;
        }

        friend istream& operator>> (istream& in, Array& arr){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
                for (int i=0; i<n;i++){
                    int value; in>>value;
                    arr.push_back(value);
                }
                return in;
        }

        void clear(){
            size = 0;
        }

        int getsize(){return size;}

        void sort(){
            if(size>1) merge_sort(0,size-1);
        }

    private:
        void resize(){
            capacity*=2;
            int *tmp = new int[capacity];
            for (int i =0; i<size;i++) tmp[i] = data[i];
            delete[] data; data = tmp;
        }

        void merge(int left, int right, int mid){
            int n1 = mid-left+1; int n2 = right-mid;
            int* t1 = new int[n1]; int* t2 = new int[n2];

            Arrayiterator array_l; array_l.current = data + left;
            Arrayiterator array_r; array_r.current = data + mid + 1;

            Arrayiterator t1_i; t1_i.current = t1;
            Arrayiterator t2_i; t2_i.current = t2;

            for (int i = 0; i<n1;i++) t1[i] = array_l[i];
            for (int i = 0; i<n2;i++) t2[i] = array_r[i];

            t1_i.current = t1; t2_i.current = t2;
            Arrayiterator t1_end = t1_i + n1; Arrayiterator t2_end = t2_i + n2;
            Arrayiterator res_it; res_it.current = data + left;

            while(t1_i<t1_end && t2_i<t2_end){
                if (*t1_i <= *t2_i){    
                    *res_it = *t1_i;
                    ++t1_i;
                } else if (*t1_i>*t2_i){
                    *res_it = *t2_i;
                    ++t2_i;
                }
                ++res_it;
            }

            while(t1_i<t1_end){
                *res_it = *t1_i;
                ++t1_i; ++res_it;
            }
            while(t2_i<t2_end){
                *res_it = *t2_i;
                ++t2_i; ++res_it;
            }

            delete[]t1; delete[]t2;
        }

        void merge_sort(int left, int right){
            if (left >= right) return;
            int middle = left+(right-left)/2;

            merge_sort(left,middle); merge_sort(middle+1,right); merge(left,right,middle);
        }
};

int main(){
    Array arr; cin >> arr;
    arr.sort();
    cout << arr << endl; 
    return 0;
}

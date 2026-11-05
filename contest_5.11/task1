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

            for (int i = 0; i<n1;i++) t1[i] = data[left+i];
            for (int i = 0; i<n2;i++) t2[i] = data[mid+1+i];
            int i = 0, j = 0, k = left;
            while(i<n1 && j <n2){
                if (t1[i] <= t2[j]){
                    data[k] = t1[i];
                    i++;
                } else if (t1[i]>t2[j]){
                    data[k] = t2[j];
                    j++;
                }
                k++;
            }
            while(i<n1){
                data[k] = t1[i];
                i++, k++;
            }
            while(j<n2){
                data[k]=t2[j]; j++;k++;
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

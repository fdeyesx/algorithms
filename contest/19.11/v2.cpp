#include <iostream>
#include <functional>
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

template <typename T>
class Array{
    protected:
        int size = 0; int capacity = 10; T *data;
    public:
        Array(){data = new T[capacity];}
        virtual ~Array(){delete[] data;}

        Array(const Array& arr){
            size = arr.size;
            capacity = arr.capacity;
            data = new T[capacity];
            for (int i = 0;i<size;i++) data[i] = arr.data[i];
        }

        T& operator[](int index){
            if (index<0 || index >= size) throw OverflowDataException();
            return data[index];
        }

        const Array& operator= (const Array& arr){
            if (this==&arr) throw SameDataException();

            T *newdata = new T[arr.capacity];
            for (int i = 0;i<arr.size;i++) newdata[i] = arr.data[i];
            delete[] data;
            
            data = newdata;
            size = arr.size;
            capacity = arr.capacity;
            
            return *this;
        }

        T pop_back(){
            return size == 0 ? throw EmptyDataException() : data[--size];
        }

        T pop_front(){
            if (size==0) throw EmptyDataException();
            T val = data[0];
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

        virtual void push_back(T value){
            if (size==capacity) resize();
            data[size++] = value;
        }

        virtual void push_front(T value){
            if (size==capacity) resize();
            for (int i = size; i > 0; --i) data[i] = data[i-1];
            data[0] = value; size++;
        }

        friend istream& operator>> (istream& in, Array& arr){
            int n; in>>n;
            if(n<0) throw NegativeSizeException();
                for (int i=0; i<n;i++){
                    T value; in>>value;
                    arr.push_back(value);
                }
                return in;
        }

        void clear(){
            size = 0;
        }

        int getsize(){return size;}
    private:
        void resize(){
            capacity*=2;
            T *tmp = new T[capacity];
            for (int i =0; i<size;i++) tmp[i] = data[i];
            delete[] data; data = tmp;
        }
};

//1st part
class Event{
public:
    virtual ~Event(){};
};

class ClickEvent: public Event{
    int x,y;
public:
    ClickEvent(int dot_x, int dot_y){
        x = dot_x; y = dot_y;
    }
};

class KeyEvent: public Event{
    char key;
public:
    KeyEvent(char k){
        key = k;
    }
};


//2 part
template <typename T>
class EventDispatcher{
    Array<function<void(const T&)>> listeners;
public:    
    EventDispatcher(){
        static_assert(std::is_base_of<Event, T>::value, "T must inherit from Event");
    }    

    void subscribe(std::function<void(const T&)> callback){
        listeners.push_back(callback);
    }
    void dispatch(const T& event){
        for(int i = 0; i < listeners.getsize(); i++) listeners[i](event);
    }
};

//3 part
class Button: public EventDispatcher<ClickEvent>{
public: void click(int x, int y){
        ClickEvent event(x,y);
        dispatch(event);
    }
};

class Keyboard: public EventDispatcher<KeyEvent>{
public: void pressKey(char c){
        KeyEvent event(c);
        dispatch(event);
    }
};

int main(){
    int events_number; cin>>events_number;
    Button button; 
    Keyboard keyboard;
    int clicks_count = 0;
    int keys_count = 0;

    button.subscribe([&clicks_count](ClickEvent& event){
        cout << "Click " << event.x << " " << event.y << endl;
        keys_count++;
    });
    keyboard.subscribe([&keys_count](KeyEvent& event){
        cout << "Key " << event.key << endl;
        keys_count++;
    });

    for (int i = 0; i<events_number;i++){
        string type; cin>>type;
        if(type=="CLICK"){
            int x,y; cin>>x; cin>>y;
            button.click(x,y);
        }
        else if(type=="KEY"){
            char key; cin>>key;
            keyboard.pressKey(key);
        }
    }

    cout << "Stats: clicks=" << clicks_count << ", keys=" << keys_count << endl;
    return 0;
}

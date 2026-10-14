#pragma once
#include <iostream>

class arrayerror{
    protected: std::string message; 
    public:
        arrayerror(const std::string& text) {message = text;}
        virtual ~arrayerror() {}
        std::string msg(){return message;}
};

class EmptyArrayException : public arrayerror{
    public:
        EmptyArrayException(): arrayerror("Data is empty."){}
};

class WrongTypeException : public arrayerror{
    public:
        WrongTypeException(): arrayerror("Wrong type's been entered."){}
};

class SameDataException : public arrayerror{
    public:
        SameDataException(): arrayerror("Assignment same data."){}
};

class OverflowDataException : public arrayerror{
    public:
        OverflowDataException(): arrayerror("Index's out of range."){}
};

class NegativeSizeException : public arrayerror{
    public:
        NegativeSizeException(): arrayerror("Negative number for size has been entered."){}
};

class NotFound : public arrayerror{
    public:
        NotFound(): arrayerror("Value hasn't been found."){}
};

class StackOverflowException : public arrayerror {
    public:
        StackOverflowException() : arrayerror("Limit's been reached.") {}
};

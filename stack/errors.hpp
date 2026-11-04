#pragma once
#include <iostream>

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

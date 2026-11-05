#include <iostream>
#include <cassert>
#include "stack.hpp"
using namespace std;

void tests(){
    AStack<int> ast;
    ast.push(9); ast.push(23); ast.push(7); ast.push(94);
    assert(ast.peek() == 94);
    assert(ast.pop() == 94);
    assert(ast.peek() == 7);
    assert(!ast.isEmpty());

    Limitedstack<double, AStack> lst(2); 
    lst.push(3.5); lst.push(0.3);
    assert(lst.peek() == 0.3);
    assert(lst.pop()==0.3);
    assert(lst.peek()==3.5);

    LStack<string> lst2;
    lst2.push("west");
    lst2.push("door");
    assert(lst2.pop() == "door");

    AStack<int> ast2;
    string message = "";
    try{
        ast2.pop();
    } catch (errors& e){
        message = e.msg();
    }
    assert(message != "");

    ast2 = ast;
    assert(!ast2.isEmpty());
    assert(ast2.peek()==7);
    assert(ast2.pop()==7);
    assert(ast2.peek()==23);

    cout<<"All tests were passed.\n";
}

int main(){
    tests();
    return 0;
}

#include "vector.hpp"
#include <iostream>
#include "stack.hpp"

int main()
{
    Stack<int> stack(5);
    stack.push(2);
    std::cout << stack.top() << std::endl;
}

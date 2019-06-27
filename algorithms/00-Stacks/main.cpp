#include "stack.hpp"
#include <iostream>

int main()
{
    Stack p;

    p.push(10);
    p.push(20);
    p.push(30);

    p.pop();
    p.pop();

    p.push(40);

    std::cout << "Top: " << p.get() << std::endl;
    std::cout << "Stack size: " << p.size() << std::endl;

    p.pop();

    if (p.isEmpty())
        std::cout << "Empty\n";
    else
        std::cout << "Full\n";

    return 0;
}

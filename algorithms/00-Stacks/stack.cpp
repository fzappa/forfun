#include "stack.hpp"
#include <iostream>

#define SIZE 10

Stack::Stack()
{
    array = new int[SIZE];
    top   = -1;
    max   = SIZE;
}

Stack::~Stack() { delete[] array; }

void Stack::push(int val)
{
    if (isFull()) {
        std::cout << "Overflow!\n" << std::endl;
        std::exit;
    }
    std::cout << "Push " << val << " on top of stack.\n";
    array[++top] = val;
}

int Stack::pop()
{
    if (isEmpty()) {
        std::cout << "Underflow!\n" << std::endl;
        std::exit;
    }
    std::cout << "Pop " << array[top] << " of top of stack.\n";
    return array[top--];
}

int Stack::get()
{
    if (isEmpty())
        std::exit;

    return array[top];
}

int Stack::size() { return top + 1; }

bool Stack::isFull() { return top == max - 1; }

bool Stack::isEmpty() { return top == -1; }

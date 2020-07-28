#include <iostream>

#include "src/stack.hpp"

int main() {
    Stack<int> stack;
    for (size_t i = 0; i < 1000; i++) {
        stack.push(i);
    }
    
    while (!stack.empty()) {
        std::cout << stack.pop() << " ";
    }
    std::cout << "\n";
}
#ifndef STACK
#define STACK

#include <string.h>

#define MIN_CAPACITY 100

template <typename T>
class Stack {
    T* array;
    size_t mCapacity;
    size_t mSize;
    size_t pos;

    void createArray(int size);
    void doubleCapacity();
    void shrinkCapacity();

    public:
        Stack(int capacity = MIN_CAPACITY);
        ~Stack();
        void push(T data);
        T pop();
        T top();
        bool empty();
};

// Implementation must be inside hpp for generics to work
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file

template <typename T>
Stack<T>::Stack(int capacity) {
    this->array = new T[capacity];
    this->mCapacity = capacity;
    this->mSize = 0;
    this->pos = -1;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] this->array;
}

template <typename T>
void Stack<T>::createArray(int size) {
    if (size < MIN_CAPACITY) {
        size = MIN_CAPACITY;
    }
    this->mCapacity = size;

    T* newArray = new T[this->mCapacity];
    memcpy(newArray, this->array, this->mSize * sizeof(T));

    T* tmp = this->array;
    this->array = newArray;
    delete[] tmp;
}

template <typename T>
void Stack<T>::doubleCapacity() {
    this->createArray(this->mCapacity * 2);
}

template <typename T>
void Stack<T>::shrinkCapacity() {
    this->createArray(this->mCapacity / 2);
}

template <typename T>
void Stack<T>::push(T data) {
    if (this->mSize == this->mCapacity) {
        this->doubleCapacity();
    }

    this->pos++; 
    this->mSize++;
    this->array[this->pos] = data;
}

template <typename T>
T Stack<T>::pop() {
    T data = this->top();
    this->pos--; 
    this->mSize--;

    // It should cut in half only when it is 3 times smaller than the capacity
    // to avoid a situation where removing and inserting a lot of times 
    // alternately will cause multiple doubles and shrinks. 
    if (this->mCapacity > MIN_CAPACITY && this->mSize < this->mCapacity / 3) {
        this->shrinkCapacity();
    }

    return data;
}

template <typename T>
T Stack<T>::top() {
    return this->array[this->pos];
}

template <typename T>
bool Stack<T>::empty() {
    return this->mSize == 0;
}


#endif
#ifndef STACK_HPP
#define STACK_HPP


#include <stdexcept>
/*
    Two stack implementation. One using a fixed size array, the other using
    a linked list.

    FIFO (first in first out) container

    push will add an element to the top.
    top will return the top element.
    pop will remove an element from the top.
*/

template <typename T> class ArrayImpl;
template <typename T> class LinkedListImpl;

template <typename T>
class Impl
{
public:
    /*
        Add a value to the top of the stack
    */
    virtual void push(T value) = 0;

    /*
        Get top value of the stack
    */
    virtual T top() = 0;

    /*
        Remove top value from the stack.
    */
    virtual void pop() = 0;
};

template <typename T, class Container = ArrayImpl<T>>
class Stack
{
public:
    Stack(size_t capacity):
        impl_(capacity)
    {

    }

    void push(T value)
    {
        impl_.push(value);
    }

    T top()
    {
        return impl_.top();
    }

    void pop()
    {
        return impl_.pop();
    }

private:
    Container impl_;
};


/* ---------------------------------------------------
    Like a vector, will resize.
-----------------------------------------------------*/
template<typename T>
class ArrayImpl: public Impl<T>
{
public:

    ArrayImpl(size_t capacity):
        capacity_(capacity),
        top_index_(0),
        data_(new T[capacity])
    {

    }

    ArrayImpl(const ArrayImpl& other):
        capacity_(other.capacity_),
        top_index_(other.top_index_),
        data_(new T[capacity_])
    {
        std::copy(other.data_, other.data_ + top_index_, data_);
    }

    ArrayImpl(const ArrayImpl&& other)
    {
        capacity_ = other.capacity_;
        top_index_ = other.top_index_;
        data_ = other.data_;

        other.data_ = nullptr;
    }

    ArrayImpl& operator=(const ArrayImpl& other)
    {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            top_index_ = other.top_index_;
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + top_index_, data_);
        }
        return *this;
    }

    ArrayImpl& operator=(const ArrayImpl&& other)
    {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            top_index_ = other.top_index_;
            data_ = other.data_;

            other.data_ = nullptr;
        }
        return *this;
    }

    /*
        Add a value to the top of the stack
    */
    void push(T value)
    {
        // check we did not fill the array.
        if (top_index_ == capacity_) {
            throw std::runtime_error("Container full");
        }

        data_[top_index_] = value;
        top_index_++;
    }

    /*
        Get top value of the stack
    */
    T top()
    {
        if (top_index_ < 1) {
            throw std::runtime_error("Empty stack");
        }
        return data_[top_index_ - 1];
    }

    /*
        Remove top value from the stack.
    */
    void pop()
    {
        if (top_index_ < 1) {
            throw std::runtime_error("Empty stack");
        }

        data_[top_index_].~T();
        top_index_--;
    }
private:

    /*
        Max number of element in the stack.
    */
    size_t capacity_;

    /*
        Current index of the top of the stack
    */
    size_t top_index_;

    /*
        array which contains the data
    */
    T* data_;

};

#endif

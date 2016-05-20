#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <unistd.h>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <iostream>

/*
    Really basic vector impl for learning. Miss a lot of stuff
*/
template<typename T>
class SVector
{
public:
    // Construct and allow memory
    SVector(size_t length=2):
        length_(length), data_(new T[length_]), end_(0), resize_factor_(1.5)
    {
        if (length_ < 1) {
            throw std::runtime_error("Length should be at least 1");
        }
    }

    ~SVector()
    {
        // Free array memory
        if (data_) {
            delete[] data_;
        }
    }

    // Copy constructor
    SVector(const SVector& other):
        length_(other.length_), data_(new T[other.length_]), end_(other.end_), resize_factor_(1.5)
    {
        std::copy(other.data_, other.data_ + end_, data_);
    }

    SVector& operator=(const SVector& other)
    {
        if (this != &other) {
            delete[] data_;
            length_ = other.length_;
            end_ = other.end_;
            data_ = new T[length_];
            resize_factor_ = other.resize_factor_;
            std::copy(other.data_, other.data_ + end_, data_);
        }

        return *this;
    }

    // Move constructor
    SVector(const SVector&& other):
        data_(nullptr)
    {
        length_ = other.length_;
        data_ = other.data_;
        end_ = other.end_;
        resize_factor_ = other.resize_factor_;

        // Will call destructor after..
        other.data_ = nullptr;
    }

    SVector& operator=(const SVector&& other)
    {
        if (this != &other) {
            delete[] data_;
            length_ = other.length_;
            end_ = other.end_;
            data_ = other.data_;
            resize_factor_ = other.resize_factor_;
            other.data_ = nullptr;

        }

        return *this;
    }

    /*
        Access at index i
    */
    T at(size_t index)
    {
        if (index >= size()) {
            throw std::out_of_range("SVector: index is greater than size");
        }
        return data_[index];
    }

    /*
        Size of the array. Not length_ which is the available space, but end_
    */
    size_t size() const
    {
        return end_;
    }

    /*
        Add an element at the end of the vector.
    */
    void push_back(T element)
    {
        if (end_ == length_) {
            resize(ceil(length_ * resize_factor_));
        }

        data_[end_] = element;
        end_++;
    }

private:
    // length of the data
    size_t length_;

    // Contiguous in memory.
    T* data_;

    /*
        Current end of the vector;
    */
    size_t end_;

    /*
        Will grow vector size automatically.
    */
    float resize_factor_;

    /*
        Resize by factor resize_factor;
    */
    void resize(size_t new_capacity)
    {
        // Allocate new memory
        T* new_data = new T[new_capacity];
        std::copy(data_, data_ + length_, new_data);

        // Delete and affect new array
        delete[] data_;
        data_ = new_data;
        length_ = new_capacity;

        new_data = nullptr;
    }

};

#endif /* end of include guard:  */

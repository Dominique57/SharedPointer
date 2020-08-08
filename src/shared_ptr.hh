#pragma once

#include <memory.h>

template <typename T>
class SharedPtr
{
public:
    // CTOR - DTOR
    SharedPtr(T* data);
    ~SharedPtr();

    // CTOR - more
    SharedPtr() = delete;
    SharedPtr(SharedPtr<T>& copy);
    SharedPtr(SharedPtr<T>&& move) = delete;

    // OPERATOR OVERLOADING
    T& operator*() const {return *data_; };
    T* operator->() const {return data_; };

    // METHODS
    int ref_count_get() const { return *count_; };
    T* get() const { return data_; };
private:
    int* count_;
    T* data_;
};

#include "shared_ptr.hxx"

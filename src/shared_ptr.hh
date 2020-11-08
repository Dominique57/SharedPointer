#pragma once

#include <memory.h>
#include <functional>
#include <utility>

template <typename T>
class SharedPtr
{
// Custom types
public:
    using count_t = unsigned int;
// Actual informations
private:
    SharedPtr(count_t* count, T* data)
        : packed(true), count_(count), data_(data) {}
public:
    // CTOR - DTOR
    SharedPtr(T* data);
    ~SharedPtr();

    // CTOR - more
    SharedPtr() = delete;
    SharedPtr(SharedPtr<T>& copy);
    SharedPtr(SharedPtr<T>&& move) = default;

    // Single allocation object construction
    template<typename... Args> static
    SharedPtr<T> make_shared(Args&&... args);

    // OPERATOR OVERLOADING
    T& operator*() const {return *data_; };
    T* operator->() const {return data_; };

    // METHODS
    count_t ref_count_get() const { return *count_; };
    T* get() const { return data_; };
private:
    count_t* count_;
    T* data_;

    bool packed = false;
};

#include "shared_ptr.hxx"

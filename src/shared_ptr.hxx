#include "shared_ptr.hh"
template <typename T>
SharedPtr<T>::SharedPtr(T* data)
{
    count_ = new count_t(1);
    data_ = data;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    *count_ -= 1;
    if (*count_ == 0)
    {
        delete count_;
        if (data_ != nullptr && not packed)
            delete data_;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& copy)
{
    count_ = copy.count_;
    data_ = copy.data_;
    *count_ += 1;
}

template<typename T>
template<typename... Args>
SharedPtr<T> SharedPtr<T>::make_shared(Args&&... args)
{
    void* mem = (void*)malloc(sizeof(count_t) + sizeof(T));

    count_t* count = static_cast<count_t*>(mem);
    T* data = static_cast<T*>(static_cast<void*>(count + 1));

    *count = 1;
    new (data) T(std::forward<Args>(args)...);

    return SharedPtr<T>(count, data);
}

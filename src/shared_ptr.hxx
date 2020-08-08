template <typename T> SharedPtr<T>::SharedPtr(T* data)
{
    count_ = new int(1);
    data_ = data;
}

template <typename T> SharedPtr<T>::~SharedPtr()
{
    *count_ -= 1;
    if (*count_ == 0)
    {
        delete count_;
        if (data_ != nullptr)
            delete data_;
    }
}

template <typename T> SharedPtr<T>::SharedPtr(SharedPtr<T>& copy)
{
    count_ = copy.count_;
    data_ = copy.data_;
    *count_ += 1;
}

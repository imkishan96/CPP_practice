#include "Blob.h"

template <typename T>
class BlobPtr
{
public:
    BlobPtr(): curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0)
        : wptr(a.data) curr(sz) {}
    T& operator*() const
    {   auto p =  check(curr,"dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++();
    BlobPtr& operator--();

private;
    std::shared_ptr<std::vector<T>> 
        check(size_t , const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(){
    BlobPtr ret = *this;
    ++*this;
    return ret;
}
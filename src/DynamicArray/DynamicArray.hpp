#include <iostream>
#include <cstddef>


template <typename T>
class DynamicArray {

private:            
    T* data;           
     size_t size_;
     size_t capacity_;
public:
    DynamicArray();     //Declaring the constructor
    ~DynamicArray();    //Declaring the destructor
    size_t size() const; // Returns the number of elements in the array
    bool empty() const;     // Returns true if the array is empty, false otherwise
};
#include "DynamicArray.tpp"
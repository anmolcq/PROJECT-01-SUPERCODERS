#include <iostream>
#include <cstddef>
#include <new>          


template<typename T>
class DynamicArray
{
private:

    T*      data;
    size_t  size;
    size_t  capacity;

    void grow();    // Double capacity
    void shrink();  // Halve capacity

public:

    DynamicArray();                                          // Default constructor
    ~DynamicArray();                                         // Destructor
    DynamicArray(const DynamicArray<T>& other);              // Copy constructor
    DynamicArray<T>& operator=(const DynamicArray<T>& other); // Copy assignment operator

    void   append(const T& value);           // Append to end
    T&     operator[](size_t index);         // Unchecked access
    T&     get(size_t index);                // Bound-checked access
    bool   insert(size_t index, const T& value); // Insert at index
    bool   remove(size_t index);             // Remove at index
    bool   pop_back();                       // Remove last element

    size_t getSize()     const;
    size_t getCapacity() const;
    bool   empty()       const;
};
template<typename T>
static void destroyElements(T* data, size_t count)
{
    for (size_t i = 0; i < count; i++)
        data[i].~T();   // Explicit destructor call — required when using placement new
}


template<typename T>
DynamicArray<T>::DynamicArray()
    : size(0), capacity(4), data(nullptr)
{
    // malloc gives raw memory — no constructors run yet (correct for T objects
    // that will be constructed individually via placement new later)
    data = static_cast<T*>(malloc(sizeof(T) * capacity));

    if (data == nullptr)
        throw std::bad_alloc();
}


template<typename T>
DynamicArray<T>::~DynamicArray()
{
    destroyElements(data, size);    // Call destructors on live elements
    free(data);                     // Then release raw memory
    data     = nullptr;
    size     = 0;
    capacity = 0;
}


template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : size(0), capacity(other.capacity), data(nullptr)
{
    data = static_cast<T*>(malloc(sizeof(T) * capacity));

    if (data == nullptr)
        throw std::bad_alloc();

    // Placement new: copy-constructs each element into the raw buffer.
    
    for (size_t i = 0; i < other.size; i++)
    {
        new (data + i) T(other.data[i]); // placement new — copy-construct
        size++;

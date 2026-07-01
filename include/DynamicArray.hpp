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
    DynamicArray(size_t count);                     // Constructor with initial capacity
    ~DynamicArray();                                         // Destructor
    DynamicArray(const DynamicArray<T>& other);              // Copy constructor
    DynamicArray<T>& operator=(const DynamicArray<T>& other); // Copy assignment operator

    void   append(const T& value);           // Append to end
    T&     operator[](size_t index);         // Unchecked access
    T&     get(size_t index);                // Bound-checked access
    bool   insert(size_t index, const T& value); // Insert at index
    bool   remove(size_t index);             // Remove at index
    bool   pop_back();                       // Remove last element
    const T& operator[](size_t index) const;

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
DynamicArray<T>::DynamicArray(size_t count)
    : size(count),
      capacity(count),
      data(nullptr)
{
    data = static_cast<T*>(malloc(sizeof(T) * capacity));

    if(data == nullptr)
    {
        throw std::bad_alloc();
    }

    for(size_t i = 0; i < size; ++i)
    {
        new(data + i) T();
    }
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
    }
}
template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
    if (this == &other)
        return *this;

    // Allocate new buffer BEFORE touching the existing one
    T* newData = static_cast<T*>(malloc(sizeof(T) * other.capacity));

    if (newData == nullptr)
        throw std::bad_alloc(); // *this is still intact — strong guarantee

    // Copy-construct elements into the new buffer
    size_t constructed = 0;
    try
    {
        for (size_t i = 0; i < other.size; i++)
        {
            new (newData + i) T(other.data[i]); // placement new — copy-construct
            constructed++;
        }
    }
    catch (...)
    {
        // If any copy throws, destroy what we built and free the new buffer
        for (size_t i = 0; i < constructed; i++)
            newData[i].~T();
        free(newData);
        throw; // Re-throw so caller knows assignment failed
    }

    // Everything succeeded — now replace the old buffer
    destroyElements(data, size);
    free(data);

    data     = newData;
    size     = other.size;
    capacity = other.capacity;

    return *this;
}


template<typename T>
void DynamicArray<T>::grow()
{
    size_t newCapacity = capacity * 2;

    T* newData = static_cast<T*>(malloc(sizeof(T) * newCapacity));

    if (newData == nullptr)
        throw std::bad_alloc();

    // Move-construct (or copy-construct) existing elements into the new buffer
    size_t moved = 0;
    try
    {
        for (size_t i = 0; i < size; i++)
        {
            new (newData + i) T(std::move(data[i])); // placement new — move-construct
            moved++;
        }
    }
    catch (...)
    {
        for (size_t i = 0; i < moved; i++)
            newData[i].~T();
        free(newData);
        throw;
    }

    // Destroy originals and swap buffers
    destroyElements(data, size);
    free(data);

    data     = newData;
    capacity = newCapacity;
}


template<typename T>
void DynamicArray<T>::shrink()
{
    if (capacity <= 4)
        return;

    size_t newCapacity = capacity / 2;

    T* newData = static_cast<T*>(malloc(sizeof(T) * newCapacity));

    if (newData == nullptr)
        throw std::bad_alloc();

    size_t moved = 0;
    try
    {
        for (size_t i = 0; i < size; i++)
        {
            new (newData + i) T(std::move(data[i])); // placement new — move-construct
            moved++;
        }
    }
    catch (...)
    {
        for (size_t i = 0; i < moved; i++)
            newData[i].~T();
        free(newData);
        throw;
    }

    destroyElements(data, size);
    free(data);

    data     = newData;
    capacity = newCapacity;
}


template<typename T>
void DynamicArray<T>::append(const T& value)
{
    if (size == capacity)
        grow();

    new (data + size) T(value); // placement new — copy-construct into raw slot
    size++;
}


template<typename T>
T& DynamicArray<T>::operator[](size_t index)
{
    if (index >= size)
        throw std::out_of_range("Index out of bounds");

    return data[index];
}


template<typename T>
T& DynamicArray<T>::get(size_t index)
{
    if (index >= size)
        throw std::out_of_range("Index out of bounds");

    return data[index];
}


template<typename T>
bool DynamicArray<T>::insert(size_t index, const T& value)
{
    if (index > size)
        return false;

    if (size == capacity)
        grow();

    if (size > 0)
    {
        // Construct the new last slot by moving the current last element in
        new (data + size) T(std::move(data[size - 1])); // placement new for uninitialised slot

        // Shift remaining elements right using move-assignment (already constructed)
        for (size_t i = size - 1; i > index; i--)
            data[i] = std::move(data[i - 1]);
    }
    else
    {
        // Array is empty: just placement-new at index 0
        new (data + index) T(value);
        size++;
        return true;
    }

    // Slot at index is now a moved-from (but valid, constructed) object
    data[index] = value; // copy-assign into the already-constructed slot
    size++;
    return true;
}


template<typename T>
bool DynamicArray<T>::remove(size_t index)
{
    if (index >= size)
        return false;

    // Shift elements left using move-assignment (all slots already constructed)
    for (size_t i = index; i < size - 1; i++)
        data[i] = std::move(data[i + 1]);

    // Destroy the now-duplicate element at the end
    data[size - 1].~T(); // Explicit destructor — required with placement new
    size--;

    return true;
}
template<typename T>
bool DynamicArray<T>::pop_back()
{
    if (size == 0)
        return false;

    data[size - 1].~T(); // Explicit destructor call for the removed element
    size--;

    if (size > 0 && size <= capacity / 4)
        shrink();

    return true;
}


template<typename T>
size_t DynamicArray<T>::getSize() const { return size; }

template<typename T>
size_t DynamicArray<T>::getCapacity() const { return capacity; }

template<typename T>
bool DynamicArray<T>::empty() const { return size == 0; }
template<typename T>
const T& DynamicArray<T>::operator[](size_t index) const
{
    if(index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    return data[index];
}
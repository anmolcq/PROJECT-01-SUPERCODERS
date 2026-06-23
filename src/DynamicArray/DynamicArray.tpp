template<typename T>             //template to Define the constructor
DynamicArray<T>::DynamicArray()
{
    capacity_ = 4;
    size_ = 0;
    data = new T[capacity_];
}
template<typename T>        //template to Define the destructor
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}
template<typename T>        //template to Define the size function
size_t DynamicArray<T>::size() const           
{
    return size_;
}
template<typename T>        //template to Define the empty function
bool DynamicArray<T>::empty() const
{
    return size_ == 0;
}   

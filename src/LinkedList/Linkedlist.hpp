template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    

    Node(const T& value)
        : data(value),
          next(nullptr)
    {
    }
};
template<typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;

    size_t size;
public:
    LinkedList(); // Constructor initializing an emplty Linked List 
    ~LinkedList(); // destructor destroy eveynodes
    LinkedList(const LinkedList<T>& other); //copy constructor
    LinkedList<T>& operator=(const LinkedList<T>& other);

    bool isEmpty() const; // check if the linked list is empty
    size_t getSize() const; // return the size of the linked list
    bool insertFront(const T& value); //insertion at front
    bool removeFront(); // remove the first node of the linked list
    bool insertBack(const T& value); // insert a new node at the end of the linked list
    bool removeBack(); // remove the last node of the linked list

    void display() const; //helps in debugging by displaying the content
    void clear(); // remove all nodes from the linked list`
};

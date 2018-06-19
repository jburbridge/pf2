#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

class StackNode{
public:
    int val;
    StackNode* next;
};

class Stack{

public:
    Stack();
    Stack(const Stack& s);
    ~Stack();

    bool push(const int val);
    bool pop();
    int peek() const;

    bool isEmpty() const;
    int getSize() const;
    void print() const;

private:
    StackNode* top;
    int size;
};

Stack::Stack()
{
    top = nullptr;
    size = 0;
}

Stack::Stack(const Stack& s)
{
    if(s.isEmpty())
    {
        top = nullptr;
        size = 0;
        return;
    }

    //If the Stack s is not empty, there is at least one node. Copy it.
    StackNode* ptr = s.top;
    top = new StackNode();
    top->val = ptr->val;
    top->next = nullptr;

    //Point ptr to the next node to copy, and create a second pointer to our new list
    ptr = ptr->next;
    StackNode* copy = top;

    //While there's another node to copy
    while(ptr != nullptr)
    {
        //Allocate space for a new node and move the pointer to it
        copy->next = new StackNode();
        copy = copy->next;

        //Copy the data from s
        copy->val = ptr->val;
        copy->next = nullptr;

        //Advance ptr
        ptr = ptr->next;
    }
}

Stack::~Stack()
{
    while(top != nullptr)
    {
        StackNode* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}

bool Stack::push(const int val)
{
    //Allocate space for the new node
    StackNode* newNode = new StackNode();

    //Set the new node's variables
    newNode->val = val;
    newNode->next = top;

    //Update the top pointer and the size
    top = newNode;
    size++;

    return true;
}

bool Stack::pop()
{
    //Check if the stack is empty
    if(isEmpty())
    {
        cout << "Error: Cannot pop from empty stack\n";
        return false;
    }

    //Create a pointer to the node to be deleted
    StackNode* toDelete = top;

    //Move the top
    top = top->next;

    //Delete the node
    delete toDelete;

    //Update the size
    size--;

    return true;
}

int Stack::peek() const
{
    return top->val;
}

bool Stack::isEmpty() const
{
    return top == nullptr;
}

int Stack::getSize() const
{
    return size;
}

void Stack::print() const
{
    StackNode* ptr = top;

    while(ptr != nullptr)
    {
        cout << ptr->val << " ";
        ptr = ptr->next;
    }
    cout << "\n";
}

class QueueNode
{
public:
    int val;
    QueueNode* next;
};

class Queue
{
public:
    Queue();
    ~Queue();

    bool isEmpty();
    bool enqueue(const int val);
    bool dequeue();
    int peek();

    void print() const;

private:
    void flip();

    Stack front;
    Stack back;
    int size;
};

Queue::Queue()
{
    size = 0;
}

Queue::~Queue()
{
    front.~Stack();
    back.~Stack();
    size = 0;
}

bool Queue::isEmpty()
{
    return front.isEmpty() && back.isEmpty();
}

bool Queue::enqueue(const int val)
{
    back.push(val);
    size++;
    return true;
}

bool Queue::dequeue()
{
    if(front.isEmpty())
        flip();

    front.pop();
    size--;

    return true;
}

int Queue::peek()
{
    if(front.isEmpty())
        flip();

    return front.peek();
}

void Queue::print() const
{
    front.print();

    Stack secondHalf(back);
    Stack helper;

    while(!secondHalf.isEmpty())
    {
        helper.push(secondHalf.peek());
        secondHalf.pop();
    }

    helper.print();
    cout << "\n";
}

void Queue::flip()
{
    while(!back.isEmpty())
    {
        front.push(back.peek());
        back.pop();
    }
}

int main()
{
    Queue q;
    const int size = 10;

    //Enqueue some nodes
    srand(time(NULL));
    cout << "The initial queue should be:\n";
    for(int i = 0; i < size; i++)
    {
        int value = rand() % 100;
        q.enqueue(value);
        cout << value << " ";
    }
    cout << "\n";

    cout << "\n The actual queue is:";
    q.print();

    //Dequeue some nodes
    for(int i = 0; i < 3; i++)
        q.dequeue();

    cout << "After dequeueing some nodes:\n";
    q.print();

    return 0;
}

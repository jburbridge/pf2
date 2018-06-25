#include <cstdlib>
#include <ctime>
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
        cout << ptr->val << "\n";
        ptr = ptr->next;
    }
}

int main()
{
    //Seed the RNG
    srand(time(NULL));

    //Create an empty stack
    Stack s;

    //Check to see if stack is empty
    cout << (s.isEmpty() ? "Stack is empty" : "Stack is full") << "\n";

    //Test the push function
    for(int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        s.push(val);
        cout << "After pushing " << val << "...\n";
        cout << "===========\n";
        s.print();
        cout << "===========\n";
    }

    //Test the pop function
    for(int i = 0; i < 10; i++)
    {
        s.pop();
        cout << "After popping top node...\n";
        cout << "===========\n";
        s.print();
        cout << "===========\n";
    }

    //Try to pop from an empty stack
    s.pop();

    //Test the peek function
    s.push(7);
    cout << s.peek() << "\n";

    s.push(23);
    s.push(19);
    s.push(5);

    Stack s2(s);
    s.print();
    s2.print();


    return 0;
}

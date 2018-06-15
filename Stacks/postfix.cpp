#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
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

    void push(const int val);
    bool pop(int& output);
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
        return;

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

void Stack::push(const int val)
{
    //Allocate space for the new node
    StackNode* newNode = new StackNode();

    //Set the new node's variables
    newNode->val = val;
    newNode->next = top;

    //Update the top pointer and the size
    top = newNode;
    size++;
}

bool Stack::pop(int& output)
{
    //Check if the stack is empty
    if(isEmpty())
    {
        cout << "Error: Cannot pop from empty stack\n";
        return false;
    }

    //Create a pointer to the node to be deleted, and save the value we're removing
    StackNode* toDelete = top;
    output = toDelete->val;

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
    ifstream fin;
    fin.open("expression.txt");

    Stack s;

    string input;

    while(fin >> input)
    {
        if(input[0] >= '0' && input[0] <= '9')
            s.push(stoi(input));

        else
        {
            int left, right;
            s.pop(right);
            s.pop(left);

            int result;

            if(input == "+")
                result = left + right;
            else if(input == "-")
                result = left - right;
            else if(input == "*")
                result = left * right;
            else if(input == "/")
                result = left / right;
            else
            {
                cout << "Error: Operator '" << input << "' not supported\n";
                return -1;
            }

            cout << "Computed " << left << " " << input << " " << right << " and got result = " << result << "\n";
            s.push(result);
        }

        cout << "\nStack:\n";
        s.print();
    }

    fin.close();
    return 0;
}

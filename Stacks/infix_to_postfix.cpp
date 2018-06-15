#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

class StackNode{
public:
    char data;
    StackNode* next;
};

class Stack{

public:
    Stack();
    Stack(const Stack& s);
    ~Stack();

    void push(const char data);
    bool pop(char& output);
    char peek() const;

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
    top->data = ptr->data;
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
        copy->data = ptr->data;
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

void Stack::push(const char data)
{
    //Allocate space for the new node
    StackNode* newNode = new StackNode();

    //Set the new node's variables
    newNode->data = data;
    newNode->next = top;

    //Update the top pointer and the size
    top = newNode;
    size++;
}

bool Stack::pop(char& output)
{
    //Check if the stack is empty
    if(isEmpty())
    {
        cout << "Error: Cannot pop from empty stack\n";
        return false;
    }

    //Create a pointer to the node to be deleted, and save the value we're removing
    StackNode* toDelete = top;
    output = toDelete->data;

    //Move the top
    top = top->next;

    //Delete the node
    delete toDelete;

    //Update the size
    size--;

    return true;
}

char Stack::peek() const
{
    if(isEmpty())
        return 0;
    else
        return top->data;
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
        cout << ptr->data << "\n";
        ptr = ptr->next;
    }
}



int main()
{
    ifstream fin;
    fin.open("infix.txt");

    Stack s;

    string input;
    string output = "";

    while(fin >> input)
    {
        cout << "\nInput = " << input << "\n";

        if(input[0] >= '0' && input[0] <= '9')
            output += input + " ";

        else if(input == "(")
            s.push(input[0]);

        else if(input == "+" || input == "-")
        {
            cout << "s.peek = " << s.peek() << "\n";
            while(!s.isEmpty() && s.peek() != '(')
            {
                char out;
                s.pop(out);
                output += out;
                output += " ";
            }

            s.push(input[0]);
        }

        else if(input == "*" || input == "/")
        {
            while(!s.isEmpty() && s.peek() != '(' && s.peek() != '+' && s.peek() != '-')
            {
                char out;
                s.pop(out);
                output += out;
                output += " ";
            }

            s.push(input[0]);
        }

        else
        {
            char out;

            while(!s.isEmpty() && s.peek() != '(')
            {
                s.pop(out);
                output += out;
                output += " ";
            }

            s.pop(out);


        }

        cout << "Stack:\n";
        s.print();
        cout << "Output = " << output << "\n";

    }

    fin.close();
    return 0;
}


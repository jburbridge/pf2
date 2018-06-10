#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Node
{
    public:
        int value;
        Node* next;
};

class SinglyLinkedList
{
    public:
        SinglyLinkedList();
        SinglyLinkedList(const SinglyLinkedList& _copy);
        ~SinglyLinkedList();

        bool Search(const int _value);
        bool Insert(const int _value);
        bool Delete(const int _value);
        SinglyLinkedList* operator+(const SinglyLinkedList& that);

        bool isEmpty();
        void Print(const bool printAddresses = false);

        Node* head;

    private:
};

SinglyLinkedList::SinglyLinkedList()
{
    head = nullptr;
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& _copy)
{
    //Create a dummy node in our new list
    Node* c = new Node();
    head = c;

    //Make a pointer to the beginning of the list we want to copy
    Node* ptr = _copy.head;

    //While that pointer is valid
    while(ptr != nullptr)
    {
        //Make a new blank node in our list
        c->next = new Node();
        c = c->next;

        //Copy the current node from the copy list
        c->value = ptr->value;
        c->next = nullptr;

        //Advance the pointer in the copy list
        ptr = ptr->next;
    }

    //Delete that dummy node we created at the beginning
    c = head;
    head = c->next;
    delete c;
}

SinglyLinkedList::~SinglyLinkedList()
{
    //Keep deleting the head until there's nothing left
    while(head != nullptr)
    {
        Node* ptr = head;
        head = head->next;
        delete ptr;
    }
}

bool SinglyLinkedList::Search(const int _value)
{
    //Create a pointer to the head
    Node* ptr = head;

    //While the pointer is valid and we haven't found the node we're looking for, advance the pointer
    while(ptr != nullptr && ptr->value != _value)
        ptr = ptr->next;

    //If we found the node, this expression will be true. Otherwise, false.
    return ptr != nullptr;
}

bool SinglyLinkedList::Insert(const int _value)
{
    //Create new node and point it to the head
    Node* newNode = new Node();
    newNode->value = _value;
    newNode->next = head;

    //Update the head
    head = newNode;
    return true;
}

bool SinglyLinkedList::Delete(const int _value)
{
    Node* current = head;
    Node* previous = head;

    //Advance current and previous until we find the node or we search the whole list
    while(current != nullptr && current->value != _value)
    {
        previous = current;
        current = current->next;
    }

    //If current is null, we searched the whole list and found nothing (or the list was empty)
    if(current == nullptr)
        return false;

    //If we're deleting the head, update the head. Else, reroute prev->next
    if(current == head)
        head = head->next;
    else
        previous->next = current->next;

    //It is now safe to delete the node
    delete current;

    return true;
}

SinglyLinkedList* SinglyLinkedList::operator+(const SinglyLinkedList& that)
{
    //Create our new list
    SinglyLinkedList* result = new SinglyLinkedList();

    //Create a dummy node in our new list
    Node* c = new Node();
    result->head = c;

    //Make a pointer to the beginning of this
    Node* ptr = this->head;

    //While that pointer is valid
    while(ptr != nullptr)
    {
        //Make a new blank node in our list
        c->next = new Node();
        c = c->next;

        //Copy the current node from this
        c->value = ptr->value;
        c->next = nullptr;

        //Advance the pointer in this
        ptr = ptr->next;
    }

    //Point ptr to the beginning of that
    ptr = that.head;

    //While that pointer is valid
    while(ptr != nullptr)
    {
        //Make a new blank node in our list
        c->next = new Node();
        c = c->next;

        //Copy the current node from that
        c->value = ptr->value;
        c->next = nullptr;

        //Advance the pointer in that
        ptr = ptr->next;
    }

    //Delete that dummy node we created at the beginning
    c = result->head;
    result->head = c->next;
    delete c;

    //Return a pointer to our new list
    return result;
}

bool SinglyLinkedList::isEmpty()
{
    //Check if the head is null
    return head == nullptr;
}

void SinglyLinkedList::Print(const bool printAdresses)
{
    //If the list is empty, do nothing
    if(isEmpty())
        return;

    //Make a pointer to the head of the list
    Node* ptr = head;

    //While the pointer points to a valid node, print and move forward
    while(ptr != nullptr)
    {
        if(printAdresses)
            cout << ptr << " " << ptr->value << " " << ptr->next << "\n";

        else
            cout << ptr->value << " -> ";

        ptr = ptr->next;
    }
    cout << "x\n";
}

int main()
{
    SinglyLinkedList l;

    srand(time(NULL));
    const int size = 10;

    for(int i = 0; i < size; i++)
        l.Insert(rand() % 8);

    l.Print();

    //#1: Write code to delete duplicates from a singly linked list

  /*  Node* current = l.head;

    while(current != nullptr)
    {
        Node* runner = current;

        while(runner->next != nullptr)
        {
            if(current->value == runner->next->value)
            {
                Node* toDel = runner->next;
                runner->next = toDel->next;
                delete toDel;
            }
            else
                runner = runner->next;
        }

        current = current->next;
    }

    l.Print();*/

    //#2: Design an algorithm to find the kth to last node (with no tail pointer)
   /* Node* current = l.head;
    Node* runner = current;

    int k = 4;
    for(int i = 0; i < k - 1; i++)
        runner = runner->next;

    while(runner->next != nullptr)
    {
        runner = runner->next;
        current = current->next;
    }

    cout << "The " << k << "th to last node contains a " << current->value << "\n";*/

    //#3: Design a algorithm to delete a node from the middle of a linked list
    //     given only access to that node (you don't get the head pointer)

    /*int k = 5;
    Node* toDel = l.head;
    for(int i = 0; i < k; i++)
        toDel = toDel->next;

    Node* toDelCopy = toDel->next;
    toDel->value = toDel->next->value;
    toDel->next = toDel->next->next;
    delete toDelCopy;

    l.Print();
*/

    return 0;
}

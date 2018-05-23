#include <cstdlib>
#include <iostream>
using namespace std;

class Node
{
    public:
        int value;
        Node* next;
        Node* prev;
};

class DoublyLinkedList
{
    public:
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& _copy);
        ~DoublyLinkedList();

        bool Search(const int _value);
        bool Insert(const int _value);
        bool Delete(const int _value);
        DoublyLinkedList* operator+(const DoublyLinkedList& that);

        bool isEmpty();
        void Print();

    private:
        Node* head;
};

DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& _copy)
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
        c->next->prev = c;
        c = c->next;

        //Copy the current node from the copy list
        c->value = ptr->value;
        c->next = nullptr;

        //Advance the pointer in the copy list
        ptr = ptr->next;
    }

    //Delete that dummy node we created at the beginning
    c = head;
    head = head->next;
    head->prev = nullptr;
    delete c;
}

DoublyLinkedList::~DoublyLinkedList()
{
    //Keep deleting the head until there's nothing left
    while(head != nullptr)
    {
        Node* ptr = head;
        head = head->next;
        delete ptr;
    }
}

bool DoublyLinkedList::Search(const int _value)
{
    //Create a pointer to the head
    Node* ptr = head;

    //While the pointer is valid and we haven't found the node we're looking for, advance the pointer
    while(ptr != nullptr && ptr->value != _value)
        ptr = ptr->next;

    //If we found the node, this expression will be true. Otherwise, false.
    return ptr != nullptr;
}

bool DoublyLinkedList::Insert(const int _value)
{
    //Create new node and point it to the head
    Node* newNode = new Node();
    newNode->value = _value;
    newNode->next = head;
    newNode->prev = nullptr;

    //Update the head
    if(head != nullptr)
        head->prev = newNode;
    head = newNode;

    return true;
}

bool DoublyLinkedList::Delete(const int _value)
{
    Node* current = head;

    //Advance current and previous until we find the node or we search the whole list
    while(current != nullptr && current->value != _value)
        current = current->next;

    //If current is null, we searched the whole list and found nothing (or the list was empty)
    if(current == nullptr)
        return false;

    //If we're deleting the head, move the head and set new head's prev to nullptr
    if(current == head)
    {
        head = head->next;
        head->prev = nullptr;
    }

    //Otherwise, have prev node's next ptr skip current node
    else
    {
        current->prev->next = current->next;

        //If we're not deleting the tail node, correct the next node's prev ptr
        if(current->next != nullptr)
            current->next->prev = current->prev;
    }

    //It is now safe to delete the node
    delete current;

    return true;
}

DoublyLinkedList* DoublyLinkedList::operator+(const DoublyLinkedList& that)
{
    //Create our new list
    DoublyLinkedList* result = new DoublyLinkedList();

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
        c->next->prev = c;
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
        c->next->prev = c;
        c = c->next;

        //Copy the current node from that
        c->value = ptr->value;
        c->next = nullptr;

        //Advance the pointer in that
        ptr = ptr->next;
    }

    //Delete that dummy node we created at the beginning
    c = result->head;
    result->head = result->head->next;
    result->head->prev = nullptr;
    delete c;

    //Return a pointer to our new list
    return result;
}

bool DoublyLinkedList::isEmpty()
{
    //Check if the head is null
    return head == nullptr;
}

void DoublyLinkedList::Print()
{
    //If the list is empty, do nothing
    if(isEmpty())
        return;

    //Make a pointer to the head of the list
    Node* ptr = head;

    //While the pointer points to a valid node, print and move forward
    while(ptr != nullptr)
    {
        cout << ptr->prev << " " << ptr->value << " " << ptr->next << "\n";
        ptr = ptr->next;
    }
}

int main()
{
    /***************
     * Test Insert *
     ***************/

    cout << "List 1:\n";
    DoublyLinkedList L1;

    //Case 1: Inserting into empty list
    L1.Insert(10);
    L1.Print();

    //Case 2: General case
    for(int i = 0; i < 9; i++)
    {
        int val = rand() % 100;
        L1.Insert(val);
        L1.Print();
    }

    /***************
     * Test Search *
     ***************/

    cout << "\n\nList 2:\n";
    DoublyLinkedList L2;

    //Case 1: Searching an empty list
    cout << "The number 5 was " << (L2.Search(5) ? "" : "not ") << "found.\n";

    L2.Insert(10);
    L2.Insert(4);
    L2.Insert(32);
    L2.Insert(99);
    L2.Print();

    //Case 2: Searching for something that's not there
    cout << "The number 23 was " << (L2.Search(23) ? "" : "not ") << "found.\n";

    //Case 3a: Searching for the head node
    cout << "The number 99 was " << (L2.Search(99) ? "" : "not ") << "found.\n";

    //Case 3b: Searching for the tail node
    cout << "The number 10 was " << (L2.Search(10) ? "" : "not ") << "found.\n";

    //Case 3c: Searching for a middle node
    cout << "The number 4 was " << (L2.Search(4) ? "" : "not ") << "found.\n";

    /***************
     * Test Delete *
     ***************/

    cout << "\n\nList 3:\n";
    DoublyLinkedList L3;

    //Case 1: Trying to delete from empty list
    L3.Delete(5);

    L3.Insert(21);
    L3.Insert(22);
    L3.Insert(34);
    L3.Insert(5);
    L3.Insert(73);
    L3.Print();

    //Case 2: Trying to delete something that doesn't exist
    cout << "\nThe number 11 was " << (L3.Delete(11) ? "successfully deleted." : "not found.") << "\n";
    L3.Print();

    //Case 3a: Deleting the head
    cout << "\nThe number 73 was " << (L3.Delete(73) ? "successfully deleted." : "not found.") << "\n";
    L3.Print();

    //Case 3b: Deleting the tail
    cout << "\nThe number 21 was " << (L3.Delete(21) ? "successfully deleted." : "not found.") << "\n";
    L3.Print();

    //Case 3c: Deleting a middle node
    cout << "\nThe number 34 was " << (L3.Delete(34) ? "successfully deleted." : "not found.") << "\n";
    L3.Print();

    /*************************
     * Test Copy Constructor *
     *************************/

     cout << "\n\nList 4:\n";
     DoublyLinkedList L4(L1);
     L4.Print();

    /*******************
     * Test Operator + *
     *******************/

     cout << "\n\nList 5:\n";
     DoublyLinkedList* L5;
     L5 = L1 + L2;
     L5->Print();

    return 0;
}


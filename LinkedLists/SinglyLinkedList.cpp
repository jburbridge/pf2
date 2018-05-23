#include <cstdlib>
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
        void Print(const bool printAddresses);

    private:
        Node* head;
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
    bool printAddresses = false;

    /***************
     * Test Insert *
     ***************/

    cout << "List 1:\n";
    SinglyLinkedList L1;

    //Case 1: Inserting into empty list
    L1.Insert(10);
    L1.Print(printAddresses);

    //Case 2: General case
    for(int i = 0; i < 9; i++)
    {
        int val = rand() % 100;
        L1.Insert(val);
        L1.Print(printAddresses);
    }

    /***************
     * Test Search *
     ***************/

    cout << "\n\nList 2:\n";
    SinglyLinkedList L2;

    //Case 1: Searching an empty list
    cout << "The number 5 was " << (L2.Search(5) ? "" : "not ") << "found.\n";

    L2.Insert(10);
    L2.Insert(4);
    L2.Insert(32);
    L2.Insert(99);
    L2.Print(printAddresses);

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
    SinglyLinkedList L3;

    //Case 1: Trying to delete from empty list
    L3.Delete(5);

    L3.Insert(21);
    L3.Insert(22);
    L3.Insert(34);
    L3.Insert(5);
    L3.Insert(73);
    L3.Print(printAddresses);

    //Case 2: Trying to delete something that doesn't exist
    cout << "\nThe number 11 was " << (L3.Delete(11) ? "successfully deleted." : "not found.") << "\n";
    L3.Print(printAddresses);

    //Case 3a: Deleting the head
    cout << "\nThe number 73 was " << (L3.Delete(73) ? "successfully deleted." : "not found.") << "\n";
    L3.Print(printAddresses);

    //Case 3b: Deleting the tail
    cout << "\nThe number 21 was " << (L3.Delete(21) ? "successfully deleted." : "not found.") << "\n";
    L3.Print(printAddresses);

    //Case 3c: Deleting a middle node
    cout << "\nThe number 34 was " << (L3.Delete(34) ? "successfully deleted." : "not found.") << "\n";
    L3.Print(printAddresses);

    /*************************
     * Test Copy Constructor *
     *************************/

     cout << "\n\nList 4:\n";
     SinglyLinkedList L4(L1);
     L4.Print(printAddresses);

    /*******************
     * Test Operator + *
     *******************/

     cout << "\n\nList 5:\n";
     SinglyLinkedList* L5;
     L5 = L1 + L2;
     L5->Print(printAddresses);

    return 0;
}

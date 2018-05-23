#include <cstdlib>
#include <iostream>
using namespace std;

class Node
{
    public:
        int value;
        Node* next;
};

class CircularlyLinkedList
{
    public:
        CircularlyLinkedList();
        CircularlyLinkedList(const CircularlyLinkedList& _copy);
        ~CircularlyLinkedList();

        bool Search(const int _value);
        bool Insert(const int _value);
        bool Delete(const int _value);
        CircularlyLinkedList* operator+(const CircularlyLinkedList& that);

        bool isEmpty() const;
        void Print(const bool printAddresses);

    private:
        Node* head;
};

CircularlyLinkedList::CircularlyLinkedList()
{
    head = nullptr;
}

CircularlyLinkedList::CircularlyLinkedList(const CircularlyLinkedList& _copy)
{
    //If the copy is an empty list, do nothing
    if(_copy.isEmpty())
        return;

    //Create a dummy node in our new list
    Node* c = new Node();
    head = c;

    //Make a pointer to the beginning of the list we want to copy
    Node* ptr = _copy.head;

    //While that pointer is valid
    do
    {
        //Make a new blank node in our list
        c->next = new Node();
        c = c->next;

        //Copy the current node from the copy list
        c->value = ptr->value;
        c->next = head->next;

        //Advance the pointer in the copy list
        ptr = ptr->next;
    } while(ptr != _copy.head);

    //Delete that dummy node we created at the beginning
    c = head;
    head = c->next;
    delete c;
}

CircularlyLinkedList::~CircularlyLinkedList()
{
    //Case 1: List is empty
    if(isEmpty())
        ;

    //Case 2: List has one node
    else if(head->next == head)
        delete head;

    //Case 3: List has 2 or more nodes
    else
    {
        Node* oldHead = head;

        do
        {
            Node* ptr = head;
            head = head->next;
            delete ptr;

        } while(head != oldHead);
    }

    //All cases: remove dangling reference
    head = nullptr;
}

bool CircularlyLinkedList::Search(const int _value)
{
    if(isEmpty())
        return false;

    //Create a pointer to the head
    Node* ptr = head;

    //While the pointer is valid and we haven't found the node we're looking for, advance the pointer
    while(ptr->next != head && ptr->value != _value)
        ptr = ptr->next;

    //If we found the node, this expression will be true. Otherwise, false.
    return ptr->value == _value;
}

bool CircularlyLinkedList::Insert(const int _value)
{
    //Create new node and point it to the head
    Node* newNode = new Node();
    newNode->value = _value;
    newNode->next = head;

    //Update the head
    head = newNode;
    if(head->next == nullptr)
        head->next = head;

    //Update the tail pointer
    else
    {
        Node* ptr = head->next;
        while(ptr->next != head->next)
                ptr = ptr->next;
        ptr->next = head;
    }
    return true;
}

bool CircularlyLinkedList::Delete(const int _value)
{
    if(isEmpty())
        return false;

    Node* current = head;
    Node* previous = head;

    //Advance current and previous until we find the node or we search the whole list
    while(current->next != head && current->value != _value)
    {
        previous = current;
        current = current->next;
    }

    //If we didn't find the value, there's nothing to delete
    if(current->value != _value)
        return false;

    //If we're deleting the only node in the list, make sure to remove the dangling reference
    else if(head->next == head)
    {
        delete head;
        head = nullptr;
    }

    //If we're deleting the head and there are at least 2 nodes in the list,
    //       update the head and tail. Else, reroute prev->next.
    if(current == head)
    {
        head = head->next;
        Node* ptr = head;
        while(ptr->next != current)
                ptr = ptr->next;
        ptr->next = head;
    }
    else
        previous->next = current->next;

    //It is now safe to delete the node
    delete current;

    return true;
}

CircularlyLinkedList* CircularlyLinkedList::operator+(const CircularlyLinkedList& that)
{
    //Create our new list
    CircularlyLinkedList* result = new CircularlyLinkedList();

    //Create a dummy node in our new list
    Node* c = new Node();
    result->head = c;

    //Make a pointer to the beginning of this
    Node* ptr = this->head;

    //While that pointer is valid
    if(ptr != nullptr)
    {
        do
        {
            //Make a new blank node in our list
            c->next = new Node();
            c = c->next;

            //Copy the current node from this
            c->value = ptr->value;
            c->next = nullptr;

            //Advance the pointer in this
            ptr = ptr->next;
        } while(ptr != this->head);
    }

    //Point ptr to the beginning of that
    ptr = that.head;

    //While that pointer is valid
    if(ptr != nullptr)
    {
        do
        {
            //Make a new blank node in our list
            c->next = new Node();
            c = c->next;

            //Copy the current node from that
            c->value = ptr->value;
            c->next = nullptr;

            //Advance the pointer in that
            ptr = ptr->next;
        } while(ptr != that.head);
    }

    //Delete that dummy node we created at the beginning
    c->next = result->head->next;
    c = result->head;
    result->head = c->next;
    delete c;

    //Return a pointer to our new list
    return result;
}

bool CircularlyLinkedList::isEmpty() const
{
    //Check if the head is null
    return head == nullptr;
}

void CircularlyLinkedList::Print(const bool printAdresses)
{
    //If the list is empty, do nothing
    if(isEmpty())
        return;

    //Make a pointer to the head of the list and print head
    Node* ptr = head;

    //While the pointer points to a valid node, print and move forward
    do
    {
        if(printAdresses)
            cout << ptr << " " << ptr->value << " " << ptr->next << "\n";
        else
            cout << ptr->value << " -> ";

        ptr = ptr->next;
    } while(ptr != head);
}

int main()
{
    bool printAddresses = true;

    /***************
     * Test Insert *
     ***************/

    cout << "List 1:\n";
    CircularlyLinkedList L1;

    //Case 1: Inserting into empty list
    L1.Insert(10);
    L1.Print(printAddresses);

    //Case 2: General case
    for(int i = 0; i < 9; i++)
    {
        int val = rand() % 100;
        cout << "Inserting " << val << "...\n";
        L1.Insert(val);
        L1.Print(printAddresses);
    }

    /***************
     * Test Search *
     ***************/

    cout << "\n\nList 2:\n";
    CircularlyLinkedList L2;

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
    CircularlyLinkedList L3;

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
     CircularlyLinkedList L4(L1);
     L4.Print(printAddresses);

    /*******************
     * Test Operator + *
     *******************/

     cout << "\n\nList 5:\n";
     CircularlyLinkedList* L5;
     L5 = L1 + L2;
     L5->Print(printAddresses);

    return 0;
}


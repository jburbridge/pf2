#include <fstream>
#include <iostream>
using namespace std;

template <class T>
class HashTable
{
public:
    HashTable(const int size);
    ~HashTable();

    bool contains(int key) const;
    T retrieve(int key) const;
    void insert(int key, T node);
    bool remove(int key);

    void print() const;

private:
    T* table;
    int tableSize;

    int find(int key) const;
    int hash(int key) const;

};

template <class T>
HashTable<T>::HashTable(const int size)
{
    tableSize = size;
    table = new T[tableSize];

    for(int i = 0; i < tableSize; i++)
        table[i] = nullptr;
}

template <class T>
HashTable<T>::~HashTable()
{
    for(int i = 0; i < tableSize; i++)
        if(table[i] != nullptr)
            delete table[i];
}

template <class T>
bool HashTable<T>::contains(int key) const
{
    return table[find(key)] != nullptr;
}

template <class T>
T HashTable<T>::retrieve(int key) const
{
    return table[find(key)];
}

template <class T>
void HashTable<T>::insert(int key, T node)
{
    table[find(key)] = node;
}

template <class T>
bool HashTable<T>::remove(int key)
{
    int index = find(key);

    //We didn't find the record
    if(table[index] == nullptr)
        return false;

    cout << "Deleting the following record: ";
    table[index]->print();

    delete table[index];
    table[index] = nullptr;

    return true;
}

template <class T>
void HashTable<T>::print() const
{
    cout << "___Table contents___\n";
    for(int i = 0; i < tableSize; i++)
        if(table[i] != nullptr)
            table[i]->print();
}

template <class T>
int HashTable<T>::find(int key) const
{
    int index = hash(key);
    while(table[index] != nullptr && table[index]->key() != key)
        index = (index + 1) % tableSize;
    return index;
}

template <class T>
int HashTable<T>::hash(int key) const
{
    return key % tableSize;
}

class Employee
{
public:
    Employee();
    Employee(const int _EID, const string _firstName, const string _lastName);
    ~Employee();

    int key() const;

    void setEID(const int _EID);
    void setFirstName(const string _firstName);
    void setLastName(const string _lastName);

    int getEID() const;
    string getFirstName() const;
    string getLastName() const;

    void print() const;

private:
    int EID;
    string firstName;
    string lastName;
};

Employee::Employee()
{
    EID = 0;
    firstName = "None";
    lastName = "None";
}

Employee::Employee(const int _EID, const string _firstName, const string _lastName)
{
    EID = _EID;
    firstName = _firstName;
    lastName = _lastName;
}

Employee::~Employee()
{

}

int Employee::key() const
{
    return EID;
}

void Employee::setEID(const int _EID)
{
    EID = _EID;
}

void Employee::setFirstName(const string _firstName)
{
    firstName = _firstName;
}

void Employee::setLastName(const string _lastName)
{
    lastName = _lastName;
}

int Employee::getEID() const
{
    return EID;
}

string Employee::getFirstName() const
{
    return firstName;
}

string Employee::getLastName() const
{
    return lastName;
}

void Employee::print() const
{
    cout << EID << " " << firstName << " " << lastName << "\n";
}

int main()
{
    HashTable<Employee*> ht(100);

    Employee* test;

    ifstream database;
    database.open("employees.txt");

    int eid;
    string first, last;

    while(database >> eid >> first >> last)
    {
        test = new Employee(eid, first, last);
        ht.insert(test->key(), test);
    }

    database.close();

    ht.print();

    cout << "\nTesting contains() function...\n";
    cout << "Employee #3242 is " << (ht.contains(3242) ? "" : "not ") << "in the table.\n";
    cout << "Employee #3518 is " << (ht.contains(3518) ? "" : "not ") << "in the table.\n";
    cout << "Employee #1234 is " << (ht.contains(1234) ? "" : "not ") << "in the table.\n";
    cout << "Employee #5678 is " << (ht.contains(5678) ? "" : "not ") << "in the table.\n";

    cout << "\nTesting retrieve() function...\n";
    cout << "Employee #3242 is " << (ht.contains(3242) ? ht.retrieve(3242)->getFirstName() + " " + ht.retrieve(3242)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #3518 is " << (ht.contains(3518) ? ht.retrieve(3518)->getFirstName() + " " + ht.retrieve(3518)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #1234 is " << (ht.contains(1234) ? ht.retrieve(1234)->getFirstName() + " " + ht.retrieve(1234)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #5678 is " << (ht.contains(5678) ? ht.retrieve(5678)->getFirstName() + " " + ht.retrieve(5678)->getLastName() : "not in the table.") << "\n";

    cout << "\nTesting remove() function...\n";
    ht.remove(3242);
    ht.remove(3518);
    ht.remove(1234);
    ht.remove(5678);

    ht.print();

    return 0;
}

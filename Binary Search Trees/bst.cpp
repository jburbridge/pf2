#include <iostream>
using namespace std;

class BSTNode
{
public:
    int value;
    BSTNode* left;
    BSTNode* right;
};

class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

    bool search(const int value) const;
    void insert(const int value);
    bool remove(const int value);
    void print() const;

private:
    BSTNode* root;
    BSTNode* parent(BSTNode* current, BSTNode* child);
    void destructHelper(BSTNode* current);
    bool searchHelper(const int value, BSTNode* current) const;
    void insertHelper(const int value, BSTNode*& current);
    bool removeHelper(const int value, BSTNode*& current);
    BSTNode* deleteNode(BSTNode* toDelete);
    void printHelper(BSTNode* current) const;
};

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}


BinarySearchTree::~BinarySearchTree()
{
    destructHelper(root);
}

void BinarySearchTree::destructHelper(BSTNode* current)
{
    if(current != nullptr)
    {
        destructHelper(current->left);
        destructHelper(current->right);
        delete current;
    }
}

bool BinarySearchTree::search(const int value) const
{
    return searchHelper(value, root);
}

bool BinarySearchTree::searchHelper(const int value, BSTNode* current) const
{
    if(current == nullptr)
        return false;
    else if(current->value == value)
        return true;
    else if(current->value > value)
        return searchHelper(value, current->left);
    else
        return searchHelper(value, current->right);
}

void BinarySearchTree::insert(const int value)
{
    insertHelper(value, root);
}

void BinarySearchTree::insertHelper(const int value, BSTNode*& current)
{
    if(current == nullptr)
    {
        current = new BSTNode();
        current->value = value;
        current->left = nullptr;
        current->right = nullptr;
    }

    else if(current->value >= value)
        insertHelper(value, current->left);

    else
        insertHelper(value, current->right);
}

BSTNode* BinarySearchTree::parent(BSTNode* current, BSTNode* child)
{
    if(current == nullptr || current == child)
        return nullptr;

    else if(current->left == child || current->right == child)
        return current;

    else if(current->value > child->value)
        return parent(current->left, child);

    else
        return parent(current->right, child);
}

bool BinarySearchTree::remove(const int value)
{
    return removeHelper(value, root);
}

bool BinarySearchTree::removeHelper(const int value, BSTNode*& current)
{
    //Node was not found, so return false
    if(current == nullptr)
        return false;

    //Node was found
    else if(current->value == value)
    {
        //Get the parent node
        BSTNode* p = parent(root, current);
        BSTNode* newChild = deleteNode(current);

        //Re-link the parent node to the subtree
        if(p != nullptr)
        {
            if(p->left == current)
                p->left = newChild;
            else
                p->right = newChild;
        }

        return true;
    }

    //Search left
    else if(current->value > value)
        return removeHelper(value, current->left);

    //Search right
    else if(current->value < value)
        return removeHelper(value, current->right);


}

//Delete the given node and return a pointer to the remaining subtree
BSTNode* BinarySearchTree::deleteNode(BSTNode* toDelete)
{
    BSTNode* retval;

    //If toDelete has no children, just delete it
    if(toDelete->left == nullptr && toDelete->right == nullptr)
    {
        retval = nullptr;
        delete toDelete;
    }

    //If toDelete has a right child, return pointer to it
    else if(toDelete->left == nullptr)
    {
        retval = toDelete->right;
        delete toDelete;
    }

    //If toDelete has a left child, return pointer to it
    else if(toDelete->right == nullptr)
    {
        retval = toDelete->left;
        delete toDelete;
    }

    //If toDelete has two children, return rightmost child in left subtree
    else
    {
        //Find rightmost child in left subtree
        BSTNode* ptr = toDelete->left;
        while(ptr->right != nullptr)
            ptr = ptr->right;

        //Copy its value into the one we were originally going to delete
        int temp = ptr->value;

        //Delete the rightmost child
        BSTNode* p = parent(toDelete, ptr);
        BSTNode* newChild = deleteNode(ptr);
        if(p != nullptr)
        {
            if(p->left == ptr)
                p->left = newChild;
            else
                p->right = newChild;
        }

        toDelete->value = temp;
        retval = toDelete;
    }
    return retval;
}

void BinarySearchTree::print() const
{
    printHelper(root);
}

void BinarySearchTree::printHelper(BSTNode* current) const
{
    if(current != nullptr)
    {
        printHelper(current->left);
        cout << current->value << " ";
        printHelper(current->right);
    }
}

int main()
{
    BinarySearchTree b;

    b.insert(2);
    b.insert(1);
    b.insert(3);
    b.insert(5);
    b.insert(4);
    b.insert(10);
    b.insert(7);
    b.insert(8);
    b.insert(6);
    b.insert(9);

    b.print();
    cout << "\n";

    cout << (b.search(3) ? "3 is in the tree" : "3 is not in the tree") << "\n";
    cout << (b.search(7) ? "7 is in the tree" : "7 is not in the tree") << "\n";
    cout << (b.search(14) ? "14 is in the tree" : "14 is not in the tree") << "\n";

    b.remove(10);
    b.print();
    cout << "\n";

   /* b.remove(6);
    b.print();
    cout << "\n";

    b.remove(10);
    b.print();
    cout << "\n";*/

    return 0;
}

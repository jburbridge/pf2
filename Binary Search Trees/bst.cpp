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

    //Main operations
    bool search(const int value) const;
    void insert(const int value);
    bool remove(const int value);

    //Print functions
    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;

private:
    BSTNode* root;

    //Helper functions for recursive algorithms
    void destructHelper(BSTNode* current);
    bool searchHelper(const int value, BSTNode* current) const;
    void insertHelper(const int value, BSTNode*& current);
    BSTNode* removeHelper(const int value, BSTNode*& current);

    void printPreorderHelper(const BSTNode* current) const;
    void printInorderHelper(const BSTNode* current) const;
    void printPostorderHelper(const BSTNode* current) const;
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

bool BinarySearchTree::remove(const int value)
{
    return removeHelper(value, root);
}

BSTNode* BinarySearchTree::removeHelper(const int value, BSTNode*& current)
{
    //Node was not found, so return false
    if(current == nullptr)
        return nullptr;

    //Search left
    else if(current->value > value)
        current->left = removeHelper(value, current->left);

    //Search right
    else if(current->value < value)
        current->right = removeHelper(value, current->right);

    //Node was found
    else
    {
        if(current->left == nullptr && current->right == nullptr)
        {
            delete current;
            current = nullptr;
        }

        else if(current->left == nullptr)
        {
            BSTNode* toDelete = current;
            current = current->right;
            delete toDelete;
        }

        else if(current->right == nullptr)
        {
            BSTNode* toDelete = current;
            current = current->left;
            delete toDelete;
        }

        else
        {
            BSTNode* toDelete = current->left;
            while(toDelete->right != nullptr)
                toDelete = toDelete->right;

            current->value = toDelete->value;
            current->left = removeHelper(toDelete->value, current->left);
        }
    }

    return current;
}

void BinarySearchTree::printPreorder() const
{
    cout << "Preorder: ";
    printPreorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printPreorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        cout << current->value << " ";
        printPreorderHelper(current->left);
        printPreorderHelper(current->right);
    }
}

void BinarySearchTree::printInorder() const
{
    cout << "Inorder: ";
    printInorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printInorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        printInorderHelper(current->left);
        cout << current->value << " ";
        printInorderHelper(current->right);
    }
}

void BinarySearchTree::printPostorder() const
{
    cout << "Postorder: ";
    printPostorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printPostorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        printPostorderHelper(current->left);
        printPostorderHelper(current->right);
        cout << current->value << " ";
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

    b.printInorder();

    cout << (b.search(3) ? "3 is in the tree" : "3 is not in the tree") << "\n";
    cout << (b.search(7) ? "7 is in the tree" : "7 is not in the tree") << "\n";
    cout << (b.search(14) ? "14 is in the tree" : "14 is not in the tree") << "\n";

    b.remove(7);

    b.printPreorder();
    b.printInorder();
    b.printPostorder();


   /* b.remove(6);
    b.print();
    cout << "\n";

    b.remove(10);
    b.print();
    cout << "\n";*/

    return 0;
}

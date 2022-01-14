#include "BinaryTree.h"
#include "Utilities.h"

template <typename T>
BTreeNode<T>::BTreeNode(T myData):nodeData(myData), leftNode(nullptr), rightNode(nullptr)
{
}

template <typename T>
BTree<T>::BTree():rootNode(nullptr)
{
}

template <typename T>
void BTree<T>::Insert(T data)
{
    rootNode = InsertInternal(rootNode, data);
}

template <typename T>
BTreeNodePtr<T> BTree<T>::InsertInternal(BTreeNodePtr<T> node, T data)
{
    if(node == nullptr)
    {
        node = new BTreeNode<T>(data);
        return node;
    }
    else if (node->nodeData > data)
    {
        node->leftNode = InsertInternal(node->leftNode, data);
    }
    else
    {
        node->rightNode = InsertInternal(node->rightNode, data);
    }
    return node;
}

template <typename T>
void BTree<T>::DisplayPreOrder(BTreeNodePtr<T> node, string nodeStr)
{
    if(node == nullptr)
    {
        cout << "[" << nodeStr << "]";
        cout << "NULL";
        return;
    }
    else
    {
        cout << "[" << nodeStr << "]";
        node->Display();
        DisplayPreOrder(node->leftNode, "left");
        DisplayPreOrder(node->rightNode, "right");
    }
}

template <typename T>
void BTree<T>::DisplayInOrder(BTreeNodePtr<T> node)
{
    if(node == nullptr)
    {
        cout << "[NULL]";
        return;
    }
    else
    {
        DisplayInOrder(node->leftNode);
        node->Display();
        DisplayInOrder(node->rightNode);
    }
}


template <typename T>
void BTree<T>::DisplayPostOrder(BTreeNodePtr<T> node)
{
    if(node == nullptr)
    {
        cout << "[NULL]";
        return;
    }
    else
    {
        DisplayPostOrder(node->leftNode);
        DisplayPostOrder(node->rightNode);
        node->Display();
    }
}

template <typename T>
void BTree<T>::TraversePreOrder()
{
    DisplayPreOrder(rootNode, "root");
}

template <typename T>
void BTree<T>::TraverseInOrder()
{
    DisplayInOrder(rootNode);
}

template <typename T>
void BTree<T>::TraversePostOrder()
{
    DisplayPostOrder(rootNode);
}

template class BTreeNode<int>;
template class BTree<int>;

int main()
{
    BTree<int>* binTree = new BTree<int>();

    IntList myList = GenerateRandmomIntList(100);
    for (auto data : myList)
        binTree->Insert(data);
    binTree->TraversePreOrder();
    return 0;
}
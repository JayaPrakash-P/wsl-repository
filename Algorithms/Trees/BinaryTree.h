#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template <typename T>
class BTreeNode
{
public:
    T nodeData;
    BTreeNode* leftNode;
    BTreeNode* rightNode;

    BTreeNode(T myData);
    void Display() { cout << nodeData; };
};

template <class T>
using BTreeNodePtr = BTreeNode<T>*;

template <typename T>
class BTree
{
    BTreeNodePtr<T> rootNode;

    BTreeNodePtr<T> InsertInternal(BTreeNodePtr<T> node, T myData);
    void DisplayPreOrder(BTreeNodePtr<T>, string nodeStr);
    void DisplayInOrder(BTreeNodePtr<T>);
    void DisplayPostOrder(BTreeNodePtr<T>);

public:
    BTree();
    void Insert(T myData);
    void TraversePreOrder();  //nlr
    void TraverseInOrder();   //lnr
    void TraversePostOrder(); //lrn
};

#endif //_BINARYTREE_H_
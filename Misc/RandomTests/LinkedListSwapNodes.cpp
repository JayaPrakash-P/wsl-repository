#include<iostream>

using namespace std;

struct Node
{
    explicit Node(int data) : nodeData(data), nextNode(nullptr){}
    
    Node*   nextNode;
    int     nodeData;
};

class LinkedList
{
public:
    void Insert(int data)
    {
        Node* newNode = new Node(data);
        newNode->nextNode = nullptr;
        
        if(headNode == nullptr)
        {
            headNode = newNode;
        }
        else
        {
            Node* tempNode = headNode;
            while(tempNode->nextNode != nullptr)
                tempNode = tempNode->nextNode;
            tempNode->nextNode = newNode;
        }
    }
    
    void Swap(int data1, int data2)
    {
        cout << "Swap [" << data1 << "] with [" << data2 << "]\n";
        Node* ptr1 = FindNodePtr(data1);
        Node* ptr2 = FindNodePtr(data2);
        
        if( (ptr1 == nullptr) || (ptr2 == nullptr) )
        {
            cout << "Invalid Data - Not swapping\n";
            return;
        }

        Node* tempNode = ptr1->nextNode;
        ptr1->nextNode = ptr2->nextNode;
        ptr2->nextNode = tempNode;
        
        tempNode = headNode;
        while(tempNode != nullptr)
        {
            if(tempNode->nextNode == ptr1)
                tempNode->nextNode = ptr2;

            if(tempNode->nextNode == ptr2)
                tempNode->nextNode = ptr1;
                
            tempNode = tempNode->nextNode;
        }
    }

    void Display()
    {
        Node* tempNode = headNode;
        while(tempNode != nullptr)
        {
            cout << tempNode->nodeData << "->";
            tempNode = tempNode->nextNode;
        }
        cout << "[END]";
    }

    ~LinkedList()
    {
        Node* tempNode    = headNode;

        while(tempNode != nullptr)
        {
            Node* currentNode = tempNode;
            tempNode = tempNode->nextNode;
            delete currentNode;
            currentNode = nullptr;
        }
    }

private:

    Node* FindNodePtr(int data)
    {
        Node* tempNode = headNode;
        
        while(tempNode->nodeData != data)
            tempNode = tempNode->nextNode;
        return tempNode;
    }
    
    Node* headNode = nullptr;

};

int main()
{
    int listSize;
    LinkedList linkedList;
    cout << "Enter number of nodes in Linked List : ";
    cin >>  listSize;
    while(listSize != 0)
    {
        int data;
        cout << "Enter Node Data#" << listSize << endl;
        cin >> data;
        linkedList.Insert(data);
        listSize--;
    }
    linkedList.Display();
    int data1, data2;
    cout << "Enter Node Data to Swap : ";
    cin >> data1 >> data2;
    linkedList.Swap(data1,data2);
    linkedList.Display();

}

//Program to delete alternate nodes in linked list starting at a position

#include <iostream>
#include <memory>
#include "../Utilities/Utils.h"

struct ListNode
{
    int data;
    struct ListNode* nextNode;
};

class SingleLinkedList
{
public:
    SingleLinkedList():listHead(nullptr){}

    ~SingleLinkedList()
    {
        while(listHead != nullptr)
        {
            ListNode* tempNode = listHead;
            listHead = listHead->nextNode;
            delete tempNode;
        }
    }
    
    void Insert(int data)
    {
        ListNode* tempNode = new ListNode;
        tempNode->data = data;
        tempNode->nextNode = nullptr;
        
        if(listHead == nullptr)
        {
            listHead = tempNode;
        }
        else
        {
            ListNode* tNode = listHead;
            while(tNode->nextNode != nullptr)
                tNode = tNode->nextNode;
            tNode->nextNode = tempNode;
        }
    }

    void Display()
    {
        ListNode* tNode = listHead;
        while(tNode != nullptr)
        {
            std::cout << "[" << tNode->data << "]";
            tNode = tNode->nextNode;
        }
        std::cout << '\n';
    }

    void DeleteAlternateNodes(int startPos)
    {
        if(startPos <= 0)
            return;

        ListNode* tNode = listHead;
        ListNode* prevNode = nullptr;
        
        //Move to starting position
        while(startPos > 1)
        {
            startPos--; 
            prevNode = tNode; 
            tNode = tNode->nextNode;
            if(tNode == nullptr)
            {
                std::cout << " Invalid starting position : " << startPos << ", NO ACTION\n";
                return;
            }
        }

        bool deleteFlag = true;

        while(tNode != nullptr)
        {
            if(deleteFlag)
            {
                ListNode* tempNode = tNode;
                prevNode->nextNode = tempNode->nextNode;
                tNode = tNode->nextNode;
                delete tempNode;
                deleteFlag = false;
            }
            else
            {
                prevNode = tNode;
                tNode = tNode->nextNode;
                deleteFlag = true;
            } 
        }
    }
    
private:
    ListNode* listHead;
};


int main()
{
    constexpr int noOfElements = 11;
    int dataSet[noOfElements];
    std::unique_ptr<SingleLinkedList> sList = std::make_unique<SingleLinkedList>();

    GenerateRandomDataSet<int,noOfElements>(dataSet);
    for(auto & data : dataSet)
      sList->Insert(data+1);

    std::cout << "Input Data  : ";
    sList->Display();

    sList->DeleteAlternateNodes(3);

    std::cout << "Output Data : ";
    sList->Display();

    return 0;
}
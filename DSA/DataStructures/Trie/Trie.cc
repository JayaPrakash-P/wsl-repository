#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Trie {

    typedef struct TrieNode
    {
        struct TrieNode* links[26]{};
        bool isEnd;
    } TrieNode;

    TrieNode* rootNode;

public:
    Trie() {
        rootNode = new TrieNode;
        rootNode->isEnd = false;
    }
    
    void insert(string word) {

        TrieNode* temp = rootNode;
        for(auto c : word)
        {
            int index = c - 'a';
            if(temp->links[index] == nullptr)
            {
                temp->links[index] = new TrieNode;
                temp->links[index]->isEnd = false;
            }
            temp = temp->links[index];
        }
        temp->isEnd = true;
    }
    
    bool search(string word)
    {
        TrieNode* temp = rootNode;
        for(auto c : word)
        {
            int index = c - 'a';
            if(temp->links[index] == nullptr)
                return false;
            temp = temp->links[index];  
        }

        if((temp != nullptr) && (temp->isEnd == true))
            return true;
        else
            return false;
    }
    
    bool startsWith(string prefix)
    {
        TrieNode* temp = rootNode;
        for(auto c : prefix)
        {
            int index = c - 'a';
            if(temp->links[index] == nullptr)
                return false;
            temp = temp->links[index];  
        }
        return true;
    }

    void Cleanup(TrieNode* node)
    {
        for(auto i = 0 ; i < 26 ; ++i)
        {
            if(node->links[i] != nullptr)
                Cleanup(node->links[i]);
            delete node->links[i];
        }
        delete node;
        node = nullptr;
    }

    ~Trie()
    {
        cout << "Cleaning up memory...\n";
        Cleanup(rootNode);
    }
};


int main()
{
    unique_ptr<Trie> trie = make_unique<Trie>();
    trie->insert("apple");
    if(trie->search("apple"))
        cout << "apple exists...\n";
    if(trie->search(("app")))
        cout << "app exists...\n";
    if(trie->startsWith("app"))
        cout << "startsWith app exists...\n";
    trie->insert("app");
    if(trie->search(("app")))
        cout << "app exists...\n";
    return 0;
}
/* [JP] : 10 run average with default Optimization level(-O0)
Measure_AddBlocks took              : [20849ms ==> 389 ms] Approx.
Measure_FindAttributesByBlock took  : [165ms   ==> 35  ms] Approx.
Measure_FindBlocksByAttribute took  : [55420ms ==> 464 ms] Approx.
 */
/*

This program is very simple. It contains two classes: Block and Graph.

- Graphs are responsible for ownership of a collection of Blocks.
- Blocks have two pieces of data: A name (std::string) and collection of (std::string) attributes.

This Graph class supports two operations:

1. Add a Block to the Graph (AddBlock)
- When a Block is added to a Graph, it cannot share a name with any Blocks already in the Graph. If the Block's name is
already elsewhere in the graph, its name will be modified to be unique. If the block's name is already unique, it must
not be changed.
- Calling AddBlock is resource acquisition. When it comes to data management, the Graph is the owner of the Block from
this point on.
- The order of blocks in a graph does not need to be preserved.

2. Return a collection of every Block in the Graph that has a specified attribute (GetBlocksWithAttribute)

- Blocks can have any number of attributes. Attributes of a block are assumed to be unique but it is not necessary to 
  validate that. The order of attributes in a block does not need to be preserved.

There are functions below prefixed with Measure_. These _Measure functions exercise the two Graph operations previously
discussed. The goal of this exercise is to optimize the execution time of these functions:

- Measure_AddBlocks
- Measure_FindAttributesByBlock
- Measure_FindBlocksByAttribute

If you take a look at main() below, you'll see that it sends the execution time of these functions to stdout. Go ahead and
run the program as-is and it's obvious that the initial performance of these operations is very bad. If it doesn't build or
run, fix it so it does.

The program is also written very badly in many ways.

Goal: See how much better you can make it both in performance and coding style and best practices.
For reference, good solutions are able to speed up the execution time of the whole program by well
over 100 times without sacrificing code clarity.

Here are the rules:

- The dynamic behavior of the code cannot change. Don't just write code to generate the expected output, expect your solution
to be tested on different datasets.
- You ARE NOT allowed to modify the Measure_ functions or main() except to make them compile and run.
- You ARE allowed to modify the Block and Graph classes. Feel free to change the API, data structures, etc. as long as you can
do so without requiring a modification of Measure_ functions or main().
- Feel free to use any C++11 and C++14 language features, so long as they are supported on any platform. That means 
  restricting yourself the standard library, and avoiding any platform-specific extensions.
- Feel free to make any obvious, simple improvements generally.

When you're done, please send me three things:

- Your modified OptGraph.cpp file. Please add a comment tagging where you've made changes.
- A copy/paste of the program output before and after you made your changes.
- A brief description of the changes that you made.

Good luck, and feel free to get in touch if you have any specific questions.
*/

#include <stdio.h>
#include <string>
#include <list>
#include <chrono>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cassert>

class Block
{
public:
    Block() { }
    ~Block() { }

    const std::string& GetName() { return m_name; } //[JP]: Return as const reference to prevent copy.
    
    //[JP] : Parameter type updated as const reference to prevent copy.
    void SetName(const std::string& name) { m_name = name; }

    //[JP] : emplace to create in-place instead of copying a temporary
    //[JP] : Parameter type updated as const reference to prevent copy.
    void AddAttribute(std::string &attribute) { m_attributes.emplace(attribute); } 
    
    //[JP] : Return type updated as const reference to prevent copy. NRVO applied if not, probably?
    const std::unordered_set<std::string>& GetAttributes() { return m_attributes; } 
    
    //[JP] : Newly added to determine attribute presence
    bool HasAttribute(const std::string& attribute)
    {
        if(m_attributes.find(attribute) != m_attributes.end())
            return true;
        else
            return false;
    }

private://[JP] : Added and moved applicable members and methods under this
    std::string m_name;
    //[JP] : unordered_set uses Hash to bucket enabling search, insertion and removal @ constant-time
    //[JP] : Preferred to make searching for attributes via GetBlocksWithAttribute faster
    //[JP] : With deque, insertion(AdsBlocks) numbers are better but Find* performance drops
    std::unordered_set<std::string> m_attributes;
    
};

struct Graph
{
    // Adds the passed block to this graph. Potentially renames the block prior to insertion to guarantee
    // each block in the graph has a unique name.
    void AddBlock(Block* block)
    {
        // Make sure we have a unique name for this block within the content of this Graph object.
        ValidateAndAssignUniqueBlockName(block); //[JP] : Renamed and removed return. Generate and update block name in place. 

        // Add it to our collection of blocks.
        m_blockSet.emplace(block);//[JP] : emplace to create in-place(via placement new internally) instead of copying a temporary
    }

    //[JP] : Return type updated as const reference to prevent copy. NRVO applied if not, probably?
    const std::unordered_set<Block*>& GetBlocks()
    {
        return m_blockSet;
    }

    std::vector<Block*> GetBlocksWithAttribute(const std::string& attribute)//[JP] : Parameter type updated as const reference to prevent copy.
    {
        
        std::vector<Block*> blocksWithAttribute;
        
        //[JP] : Reserve ahead to prevent expansion which involves costly reallocations
        blocksWithAttribute.reserve(m_blockSet.size());
        for(auto const &block : m_blockSet)
        {
            if ( block->HasAttribute(attribute) )
                blocksWithAttribute.emplace_back(block);//[JP] : emplace_back to construct element in-place
        }

        blocksWithAttribute.shrink_to_fit(); //[JP] : Shrink the vector to accommodate skipped blocks. 
        
        return blocksWithAttribute; //[JP] : Named Return Value Optimization[NRVO] applied
        
        //[JP] : Alternate logic tried
        //std::for_each(std::begin(m_blockSet), std::end(m_blockSet), [&](auto& blockPtr)
        //{
        //    if (blockPtr->HasAttribute(attribute) )
        //        blocksWithAttribute.emplace_back(blockPtr);
        //});
    }

    ~Graph() //[JP] : Free up memory allocated for Block's
    {
        for(auto blockPtr : m_blockSet)
            if ( blockPtr != nullptr )
            {
                delete blockPtr;
                blockPtr = nullptr;
            }
    }

private: //[JP] : Added and moved applicable members and methods under this
    // Here is our collection of blocks in this graph.
    std::unordered_set<Block*> m_blockSet; //[JP] : Search, insertion, and removal of elements have constant-time complexity.
    std::unordered_map<std::string, unsigned int> m_blockNameGenMap; //[JP] : To keep track of unique key for block name generation.
   
    // Determines if the specified blockName is already the name of a block in this Graph.
    //[JP] : Renamed and made use of smaller m_blockNameGenMap to decide instead of looping through complete list of blocks.
    bool NewBlockNameRequired(const std::string& blockName)
    {
        //[JP] : If name doesn't exist in m_blockNameGenMap, it's already distinct
        if(m_blockNameGenMap.find(blockName) != m_blockNameGenMap.end())
            return true;
        else//[JP] : Add distinct name into m_blockNameGenMap and update suffix for next name as 0
            m_blockNameGenMap[blockName] = 0;
            
        return false;
    }
    
    // Generate a unique name for this block within the graph.
    // If there's no name collision, then the original Block name is returned.
    // If there is a name collision, then we will appends numbers to the name to make unique.
    // So if you call with a block named "a" and there's already a block named "a", then it will return "a1".
    // If there's already an "a1" then it will return "a2", and so on.
    // [JP] : Changed name, return type to void and updating block name in-place if required
    void ValidateAndAssignUniqueBlockName(Block* block)
    {
        std::string originalName = block->GetName();
        
        //[JP] : If name doesn't exist in map, this is a distinct block name. Just add into map and set suffix for next block
        //[JP] : as zero. If exists, append suffix and generate new name. This eliminates looping through the entire block list
        //[JP] : to confirm whether the name is already taken.
        if(NewBlockNameRequired(originalName))
        {
            //[JP] : Add Suffix# from map to generate unique name and increment the Suffix# for next use
            std::ostringstream s;
            s << originalName << m_blockNameGenMap[originalName]++;
            block->SetName(s.str());
            
            //[JP] : Alternate#1 tried
            //std::string potentialName;
            //potentialName.reserve(originalName.length() + std::to_string(UINT_MAX).length());
            //potentialName = (originalName + std::to_string(m_blockNameGenMap[originalName]));
            //block->SetName(std::move(potentialName));

            //[JP] : Alternate#2 tried
            //block->SetName(std::string(originalName + std::to_string(m_blockNameGenMap[originalName])));
        }
    }
    
};

/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// DO NOT MODIFY ANY CODE BELOW THIS POINT
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

static const int s_blockQuantity = 1000;
static const int s_attributesPerBlock = 250;

static const int s_distinctAttributes = 300;
static const int s_distinctBlockNames = 10;
static std::string s_blockBaseName("blockNameBase_");
static std::string s_attrBaseName("attributeBase_");

static std::vector<std::string> s_attrs;
static std::vector<std::string> s_blockNames;

void createBlockNames() {
    std::ostringstream s;
    for (int i = 0; i < s_distinctBlockNames; ++i) {
        s << s_blockBaseName;
        s_blockNames.push_back(s.str());
    }
}

void createAttrNames() {
    for (int i = 0; i < s_distinctAttributes; ++i) {
        std::ostringstream s;
        s << s_attrBaseName << i;
        s_attrs.push_back(s.str());
    }
}

std::chrono::milliseconds Measure_AddBlocks(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int blockNameNum = 0;
    int attrNum = 0;

    for (int i = 0; i < s_blockQuantity; ++i)
    {
        blockNameNum = ++blockNameNum % s_distinctBlockNames;

        Block* b = new Block;
        b->SetName(s_blockNames[blockNameNum]);
        for (int j = 0; j < s_attributesPerBlock; ++j)
        {
            attrNum = ++attrNum % s_distinctAttributes;
            b->AddAttribute(s_attrs[attrNum]);
        }
        graph.AddBlock(b);
    }
    auto end = std::chrono::system_clock::now();

    // Post-measurement verification

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::milliseconds Measure_FindAttributesByBlock(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int compareLength = s_attrBaseName.length();

    for (auto block : graph.GetBlocks()) {
        for (const auto& attr : block->GetAttributes()) {
            assert(attr.compare(0, compareLength, s_attrBaseName) == 0);
        }
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::milliseconds Measure_FindBlocksByAttribute(Graph& graph)
{
    auto start = std::chrono::system_clock::now();
    int compareLength = s_blockBaseName.length();

    for (const auto& attr : s_attrs) {
        for (auto block : graph.GetBlocksWithAttribute(attr)) {
            assert(block->GetName().compare(0, compareLength, s_blockBaseName) == 0);
        }
    }
    auto end = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main(int argc, char* argv[])
{
    Graph graph;
    createBlockNames();
    createAttrNames();
    
    auto timeAddBlocks = Measure_AddBlocks(graph);
    std::cout << "Measure_AddBlocks took: " << timeAddBlocks.count() << "ms.\n";

    auto timeFindAttributesByBlock = Measure_FindAttributesByBlock(graph);
    std::cout << "Measure_FindAttributesByBlock took: " << timeFindAttributesByBlock.count() << "ms.\n";
    
    auto timeFindBocksByAttribute = Measure_FindBlocksByAttribute(graph);
    std::cout << "Measure_FindBlocksByAttribute took: " << timeFindBocksByAttribute.count() << "ms.\n";
    
    std::getchar();
    
    return 0;
}

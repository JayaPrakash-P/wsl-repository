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

    const std::string& GetName() { return m_name; }
    
    void SetName(const std::string& name) { m_name = name; }

    void AddAttribute(std::string &attribute) { m_attributes.emplace(attribute); } 
    
    const std::unordered_set<std::string>& GetAttributes() { return m_attributes; } 
    
    bool HasAttribute(const std::string& attribute)
    {
        if(m_attributes.find(attribute) != m_attributes.end())
            return true;
        else
            return false;
    }

private:
    std::string m_name;
    std::unordered_set<std::string> m_attributes;
    
};

struct Graph
{
    void AddBlock(Block* block)
    {
        ValidateAndAssignUniqueBlockName(block); 

        m_blockSet.emplace(block);
    }

    const std::unordered_set<Block*>& GetBlocks()
    {
        return m_blockSet;
    }

    std::vector<Block*> GetBlocksWithAttribute(const std::string& attribute)
    {
        
        std::vector<Block*> blocksWithAttribute;
        
        blocksWithAttribute.reserve(m_blockSet.size());
        for(auto const &block : m_blockSet)
        {
            if ( block->HasAttribute(attribute) )
                blocksWithAttribute.emplace_back(block);
        }

        blocksWithAttribute.shrink_to_fit();
        
        return blocksWithAttribute;
        
    }

    ~Graph()
    {
        for(auto blockPtr : m_blockSet)
            if ( blockPtr != nullptr )
            {
                delete blockPtr;
                blockPtr = nullptr;
            }
    }

private:
    std::unordered_set<Block*> m_blockSet;
    std::unordered_map<std::string, unsigned int> m_blockNameGenMap;
   
    bool NewBlockNameRequired(const std::string& blockName)
    {
        if(m_blockNameGenMap.find(blockName) != m_blockNameGenMap.end())
            return true;
        else
            m_blockNameGenMap[blockName] = 0;
            
        return false;
    }
    
    void ValidateAndAssignUniqueBlockName(Block* block)
    {
        std::string originalName = block->GetName();
        
        if(NewBlockNameRequired(originalName))
        {
            std::ostringstream s;
            s << originalName << m_blockNameGenMap[originalName]++;
            block->SetName(s.str());
            

        }
    }
    
};


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
    
    return 0;
}

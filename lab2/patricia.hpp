
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <fstream>

namespace nPatricia{

struct TNode{
    std::string key;
    uint64_t number;
    int bitNumber; 
    TNode* left = nullptr;
    TNode* right = nullptr;
    TNode(const std::string& keyVal,const uint64_t& n,const int& b);
    TNode(const std::string& ,const uint64_t& ,const int&, TNode* , TNode* );
    TNode();
    ~TNode();
};// struct TNode

bool CheckBit(const std::string& ,const int& );
int FindBitDiffering(const std::string& , const std::string& );

class TPatriciaTrie{
    public:
    TNode* header = nullptr;
    uint16_t size = 0;

    private:
    std::tuple<TNode*,TNode*, TNode*> SearchNodeAndParent(const std::string&);
    
    public:

    TPatriciaTrie();

    TNode* Search(const std::string) const;
    
    bool Delete(std::string&);
        
    void RecurseDestroy(TNode*);
    void RecursePrint(TNode*);
};// class TPatriciaTrie
}// namespace nPatricia

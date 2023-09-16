#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
// char кодируется 1 байтом 8 * 256 = 2048

// если посмотреть на то как закодированны символы, то можно понять что для проверки нам понадобятся всего лишь первые 5 бит
// так как в задание мы можем не обращать внимание на регистр все, что нам потребуется это рассмотреть первые 5 бита
// код последних 5 бит совпадает у строчных и пропсных букв
// таким образом делая проверку или добавление заглавной буквы при наличие уже строчной будет выдавать Exist  
// 5 * 256  =1280
const int MAX_BIT_NUMBER = 1280; 


namespace nPatricia{

struct TNode{
    std::string key;
    unsigned long long number;
    int bitNumber; 
    TNode* left = nullptr;
    TNode* right = nullptr;
    TNode(const std::string& keyVal,const unsigned long long& n,const int& b)
    : key(keyVal), number(n), bitNumber(b), left(nullptr), right(nullptr){}
    TNode(const std::string& k,const unsigned long long& n,const int& bn, TNode* l, TNode* r)
    : key(k), number(n), bitNumber(bn), left(l), right(r){}
    TNode() = default;
    ~TNode() {};
};// struct TNode

bool CheckBit(const std::string& s,const int& bitNumber){
    // сократим проверку до 1-ых 5-ти бит
    // в качестве будем передавать bitNumber  натуральные числа
    if (bitNumber < 0 || bitNumber > MAX_BIT_NUMBER) 
        throw std::runtime_error("Uncorrect bit Number was passed: " + std::to_string(bitNumber) + " in Checkbit function\n");
    int nbitNumber = bitNumber - 1;
    if (nbitNumber < 0)
        nbitNumber = 0;
    int curByteNumber  = nbitNumber / 5; // находим нужный нам char
    //std::cout << "curByteNumber: " << curByteNumber << ' ';
    int curBitNumber =  nbitNumber  % 5; // на каждую букву(char) выделяется по 8 бит, но нам нужно проверить только первые 5
    //std::cout << "curBitNumber: " << curBitNumber << '\n';
    int checkedChar = s[curByteNumber]; // char в котором мы проверяем бит
    return ((checkedChar >>  (4 - curBitNumber)) & 1) != 0;
}


int FindBitDiffering(const std::string& closerKey, const std::string& insKey){
    int bitNumber = 1;
    while (CheckBit(closerKey, bitNumber) == CheckBit(insKey,bitNumber) && (bitNumber <= closerKey.size() * 5 || bitNumber <= insKey.size()*5)){
        bitNumber += 1;
    }
    return bitNumber;
} // O(n) так как CheckBit() берет бит за O(1)

class TPatriciaTrie{
    public:
    TNode* header = nullptr;

    private:
    std::tuple<TNode*,TNode*,TNode*> SearchPlaceToInsert(const std::string& searchedKey)const{
        TNode* parentNode = header;
        TNode* prevNode = header;
        TNode* curentNode = header->left;
        while(curentNode->bitNumber > prevNode->bitNumber){
            if (nPatricia::CheckBit(searchedKey,curentNode->bitNumber)){
                if (curentNode->right->bitNumber <= curentNode->bitNumber)
                    parentNode = prevNode;
                
                prevNode = curentNode;
                curentNode = curentNode->right;
                
                
            }
            else{ // иначе по левой
                if (curentNode->left->bitNumber <= curentNode->bitNumber)
                    parentNode = prevNode;
                prevNode = curentNode; 
                curentNode = curentNode->left;
            }
        }
        return std::make_tuple(parentNode,prevNode,curentNode);

    }
    public:

    TPatriciaTrie(): header(nullptr){}
    

    TNode* Search(const std::string& searchedKey) const {
        if (header == nullptr){
            throw std::runtime_error("Header is empty cant search the key \n");
        }
        nPatricia::TNode* curNode = header->left;
        nPatricia::TNode* prevNode = header;
        // Ищем до тех пор пока не перейдем по обратной ссылке, т е либо наш бит уменьшится,либо останется прежним
        while (curNode->bitNumber > prevNode->bitNumber){
            // если бит единица идем по правой ссылке
            prevNode = curNode;
            if (nPatricia::CheckBit(searchedKey,curNode->bitNumber))
                curNode = curNode->right;
            else // иначе по левой
                curNode = curNode->left;
        }
        return curNode;
    }

    void Insert(const std::string& insKey, const int& insNum){
        if (header == nullptr){
            header = new nPatricia::TNode(insKey, insNum,0);
            header->left = header;
            std::cout << "OK\n";
            return;
        }
        // перешли по обратной ссылке, получаем максимально похожий на наш узел
        TNode* closerNode = Search(insKey);
        // проверяем наш узел на совпаженеи с ключом
        if(closerNode->key == insKey){
            std::cout << "Exist" << '\n';
            return;
        }
        // находим первый бит который будет отличаться 
        int insBit = nPatricia::FindBitDiffering(closerNode->key, insKey);
        TNode* nodeLargeIndex  = header->left;
        TNode* parendtNode = header;
        // нужно найти ноду в которой бит больше нашей 
        while ((nodeLargeIndex->bitNumber > parendtNode->bitNumber)  && (nodeLargeIndex->bitNumber < insBit)){
            parendtNode = nodeLargeIndex;
            nodeLargeIndex = nPatricia::CheckBit(insKey,nodeLargeIndex->bitNumber) ?
                            nodeLargeIndex->right :
                            nodeLargeIndex->left;
        }

        TNode* insNode = new TNode(insKey,insNum,insBit);
        std::cout << "ins Bit number" << insBit << '\n';
        std::cout << "large-node bit number" << nodeLargeIndex->bitNumber << '\n';
        // если тот бит который отличается 1 то правая ссылка ведет на самогосебя, иначе левая на самого себя
        if(nPatricia::CheckBit(insKey,insBit)){
            insNode->right = insNode;
            insNode->left = nodeLargeIndex;
        }
        else{
            insNode->left = insNode;
            insNode->right = nodeLargeIndex;
        }
        if(parendtNode->right == nodeLargeIndex)
            parendtNode->right = insNode;
        else
            parendtNode->left = insNode;
        std::cout << "OK\n";
    }

};// class TPatriciaTrie
}// namespace nPatricia




int main(){
    return 0;
}
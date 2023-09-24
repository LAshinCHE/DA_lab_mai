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
    ~TNode() { left = nullptr; right = nullptr;}
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
    void DeleteNode(TNode* node){
        std::cout << "delete : " << node->key << '\n';
        delete node;
        node = nullptr;
        std::cout << "OK\n";
    }
    std::tuple<TNode*,TNode*, TNode*> SearchNodeAndParent(std::string searchedKey){
        if (header == nullptr){
            throw std::runtime_error("Header is empty cant search the key \n");
        }
        nPatricia::TNode* curNode = header->left;
        nPatricia::TNode* prevNode = header;   
        nPatricia::TNode* prePrevious = nullptr;
        // Ищем до тех пор пока не перейдем по обратной ссылке, т е либо наш бит уменьшится,либо останется прежним
        while (curNode->bitNumber > prevNode->bitNumber){
            // если бит единица идем по правой ссылке
            prePrevious = prevNode;
            prevNode = curNode;
            if (nPatricia::CheckBit(searchedKey,curNode->bitNumber))
                curNode = curNode->right;
            else // иначе по левой
                curNode = curNode->left;
        }
        return std::make_tuple(curNode, prevNode,prePrevious);
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

    void Delete(std::string delKey){
        //1. если нет header, то и искать нечего
        if(header == nullptr){
            std::cout << "NoSuchWord\n";
            return;
        }
        //2. 1 нода header, тогда нужно проверить ключ и просто удалить ноду если ключ совпадает
        if (header->left == header){
            std::cout << "header->left == header" << '\n';
            if (header->key == delKey ){
                DeleteNode(header);
            }
            else{
                std::cout << "NoSuchWord\n";
            }
            return;
        }
        std::tuple<TNode*,TNode*,TNode*> tupleNode = SearchNodeAndParent(delKey);
        TNode* curNode = std::get<0>(tupleNode);
        TNode* prevNode = std::get<1>(tupleNode);
        TNode* prePreviousNode = std::get<2>(tupleNode);
        TNode* parentNode = (curNode->key == prevNode->key) ?
                            prePreviousNode :
                            prevNode;
        // нода с ключом delkey не найдена
        if (curNode->key != delKey){
            std::cout << "NoSuchWord\n";
            return;
        }
        // 3. у ключа который мы удаляем есть 1 обратная ссылка на самого себя
        if (curNode->left == curNode || curNode->right == curNode){
            bool rightLinkParent = CheckBit(parentNode->key,parentNode->bitNumber);
            bool leftLinkToCur = (curNode->left == curNode);
            if (rightLinkParent){
                if (leftLinkToCur){
                    std::cout << "Here1r\n";
                    parentNode->right = curNode->right;
                    DeleteNode(curNode);
                    return;
                }
                std::cout << "Herer2r\n";
                parentNode->right = curNode->left;
                DeleteNode(curNode);
                return;
            }
            else{
                if (leftLinkToCur){
                    std::cout << "Here1l\n";
                    parentNode->left = curNode->right;
                    DeleteNode(curNode);
                    return;
                }
                parentNode->left = curNode->left;
                std::cout << "Here2l\n";
                DeleteNode(curNode);
                return;
            }
        }// 3     
        // для нашей ноды prevNode есть родитель по которой мы в нее попали это будет наша prePreNode
        TNode*  q = prevNode; // нода которую пытаемся удалить (обозначение взято из лекции, для удобства выполнения задания)
        TNode* x = curNode; // нода которую надо удалить изначально (обозначение взято из лекции, для удобства выполнения задания)
        TNode* parentQ = prePreviousNode;
        // нужно найти такую ноду у которой есть обратная ссылка на q (в лекциях обозначается как p)
        TNode* p = header;;
        curNode = header->left;
        std::string newSearchedKey = q->key;
        while (p->bitNumber < curNode->bitNumber){
            p = CheckBit(newSearchedKey, curNode->bitNumber) ? 
                curNode->right : 
                curNode->left;
        }
        bool qRightLinkBackRevers = (q->right == x); //  какая ссылка обратная у q и ведет к x
        if (p->left == q)
            p->left = x;
        else
            p->right = x;
        if (parentQ->left == q)
            parentQ->left = qRightLinkBackRevers ?  // если правая ссылка обратная тогда левая содержит ребенка (ведем qParent к этому ребенку)
                            q->left :
                            q->right;
        else
            parentQ->right = qRightLinkBackRevers ? 
                    q->left : 
                    q->right;
        // присваиваем значение предидущей ноды и пытаемся уже удалить ее (в данной ситуации у curNode нет обратной ссылки)
        p->key =  q->key;
        p->number = q->number; 
        DeleteNode(q);
        std::cout << "OK\n";
        return;
    }
        
};// class TPatriciaTrie
}// namespace nPatricia




int main(){
    std::string action;
    nPatricia::TPatriciaTrie ptr;
    while(std::cin >> action){
        if (action == "+"){
            int64_t key;
            std::string value;
            std::cin >> key >> value;
            if ()
            {
                /* code */
            }
            
        }
        
    }
    return 0;
}
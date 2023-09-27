#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <fstream>

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
    uint64_t number;
    uint8_t bitNumber; 
    TNode* left = nullptr;
    TNode* right = nullptr;
    TNode(const std::string& keyVal,const uint64_t& n,const int& b)
    : key(keyVal), number(n), bitNumber(b), left(nullptr), right(nullptr){}
    TNode(const std::string& k,const uint64_t& n,const int& bn, TNode* l, TNode* r)
    : key(k), number(n), bitNumber(bn), left(l), right(r){}
    TNode() = default;
    ~TNode() { left = nullptr; right = nullptr;}
};// struct TNode

bool CheckBit(const std::string& s,const int& bitNumber){
    // сократим проверку до 1-ых 5-ти бит
    // в качестве будем передавать bitNumber  натуральные числа
    if (bitNumber < 0 || bitNumber > MAX_BIT_NUMBER) 
        throw std::runtime_error("ERROR: uncorrect bit Number was passed: " + std::to_string(bitNumber) + " in Checkbit function\n");
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
    }
    std::tuple<TNode*,TNode*, TNode*> SearchNodeAndParent(std::string searchedKey){
        if (header == nullptr){
            throw std::runtime_error("ERROR: Header is empty cant search the key \n");
        }
        nPatricia::TNode* curNode = header->left;
        nPatricia::TNode* prevNode = header;   
        nPatricia::TNode* prePrevious = nullptr;
        // Ищем до тех пор пока не перейдем по обратной ссылке, т е либо наш бит уменьшится,либо останется прежним
        while (curNode->bitNumber > prevNode->bitNumber){
            // если бит единица идем по правой ссылке
            prePrevious = prevNode;
            prevNode = curNode;
            //std::cout << "CHECK BIT \n";
            if (nPatricia::CheckBit(searchedKey,curNode->bitNumber))
                curNode = curNode->right;
            else // иначе по левой
                curNode = curNode->left;
        }
        //std::cout << "MAKE TUPLE\n";
        return std::make_tuple(curNode, prevNode,prePrevious);
    }
    public:

    TPatriciaTrie(): header(nullptr){}
    

    TNode* Search(const std::string& searchedKey) const {
        if (header == nullptr){
            return nullptr;
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

    void Insert(const std::string& insKey, const uint64_t& insNum){
        if (header == nullptr){
            header = new nPatricia::TNode{insKey,insNum,0};
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

    bool Delete(std::string delKey){
        //1. если нет header, то и искать нечего
        if(header == nullptr)
            return false;
        //2. 1 нода header, тогда нужно проверить ключ и просто удалить ноду если ключ совпадает
        if (header->left == header){
            if (header->key == delKey ){
                DeleteNode(header);
                return true;
            }
            else
                return false;
        }
        std::tuple<TNode*,TNode*,TNode*> tupleNode = SearchNodeAndParent(delKey);
        TNode* curNode = std::get<0>(tupleNode);
        TNode* prevNode = std::get<1>(tupleNode);
        TNode* prePreviousNode = std::get<2>(tupleNode);
        // TNode* parentNode = (curNode->key == prevNode->key) ?
        //                    prePreviousNode :
        //                    prevNode;
        // нода с ключом delkey не найдена
        if (curNode->key != delKey)
            return false;
        // 3. у ключа который мы удаляем есть 1 обратная ссылка на самого себя
        if (curNode == prevNode){
            //bool rightLinkParent = CheckBit(parentNode->key,parentNode->bitNumber);
            //bool leftLinkToCur = (curNode->left == curNode);
            if (prePreviousNode->left == curNode)
                prePreviousNode->left = curNode ->left == curNode ? 
                                        curNode->right :
                                        curNode->left;
            else
                prePreviousNode->right = curNode ->left == curNode ? 
                                        curNode->right :
                                        curNode->left;
            DeleteNode(curNode);
            return true;
        }// 3     
        // для нашей ноды prevNode есть родитель по которой мы в нее попали это будет наша prePreNode
        TNode* q = prevNode; // нода которую пытаемся удалить (обозначение взято из лекции, для удобства выполнения задания)
        TNode* x = curNode; // нода которую надо удалить изначально (обозначение взято из лекции, для удобства выполнения задания)
        TNode* parentQ = prePreviousNode;
        // нужно найти такую ноду у которой есть обратная ссылка на q (в лекциях обозначается как p)
        TNode* p = header;
        curNode = header->left;
        std::string newSearchedKey = q->key;
        while (p->bitNumber < curNode->bitNumber){
            p = curNode;
            curNode = CheckBit(newSearchedKey, curNode->bitNumber) ? 
                curNode->right : 
                curNode->left;
        }
        bool qRightBackLinck = CheckBit(p->key, q->bitNumber); // какая обратная ссылка ведет на q у p  
        if (p->left == q)
            p->left = x;
        else
            p->right = x;
        if (parentQ->left == q)
            parentQ->left = qRightBackLinck ?  // если правая ссылка обратная тогда левая содержит ребенка (ведем qParent к этому ребенку)
                            q->right :
                            q->left;
        else
            parentQ->right = qRightBackLinck ? 
                    q->right :
                    q->left;
        // присваиваем значение предидущей ноды и пытаемся уже удалить ее (в данной ситуации у curNode нет обратной ссылки)
        x->key =  q->key;
        x->number = q->number; 
        DeleteNode(q);
        return true;
    }
        
    void RecurseDestroy(TNode* node){
        if ((node->bitNumber <= node->left->bitNumber) && (node->left != node))
            RecurseDestroy(node->left);
        if ((node->bitNumber <= node->right->bitNumber) && (node->right != node))
            RecurseDestroy(node->right);
        DeleteNode(node);
    }
    void RecursePrint(TNode* node){
        if ((node->bitNumber <= node->left->bitNumber) && (node->left != node))
            RecursePrint(node->left);
        if ((node->bitNumber <= node->right->bitNumber) && (node->right != node))
            RecursePrint(node->right);
        std::cout << node->key << ' ' << node->number << '\n' ;
    }
};// class TPatriciaTrie
}// namespace nPatricia

class  SaveLoad{
    // переменные 
    public:
    std::string fp = "";
    // методы
    private:
    bool RecurseSave(nPatricia::TNode* node,std::ofstream& ostrm){
        if (!(ostrm << node->key << ' ' << node->number << ' ' << node->bitNumber << '\n')){
            return false;
        }
        bool noError = true;
        if ((node->bitNumber <= node->left->bitNumber) && (node->left != node)){
            noError  &= RecurseSave(node->left,ostrm);
        }
        if ((node->bitNumber <= node->right->bitNumber) && (node->right != node)){
            noError  &= RecurseSave(node->right,ostrm);
        }
        return noError;

    }
    public:
    SaveLoad(std::string filePath) : fp {filePath}{};
    bool Save(nPatricia::TPatriciaTrie* pt){
        std::ofstream ostrm(fp, std::ios_base::binary | std::ios_base::out); // поток для записи открываем в бинарном виде для чтения
        if (pt->header == nullptr){
            ostrm.clear();
            ostrm.close();
            std::cout << "ERROR: noting to save, patricia is empty\n";
            return false;
        }
        if(!(ostrm << pt->header->key << ' ' << pt->header->number << ' ' << pt->header->bitNumber << '\n')) {
            std::cout << "ERROR: can`t write header to file\n";
            return false;
        }
        if (pt->header->left == pt->header)
            return true;
        if (RecurseSave(pt->header->left, ostrm)){
            return true;
        }
        std::cout << "ERORR: recurse save wrong\n";      
        return false;
    }
    bool Load(nPatricia::TPatriciaTrie* pt){
        return false; // заглушка
    }
};

void ToLowerCase(std::string& str)
{
    for (size_t i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = (str[i] - ('A'-'a'));
		}
	}
}


int main(){
    std::string action;
    nPatricia::TPatriciaTrie* pt = new nPatricia::TPatriciaTrie;
    std::string key;
    uint64_t  number;
    while(std::cin >> action){
        if (action == "+"){
            std::cin >> key >> number;
            ToLowerCase(key);
            pt->nPatricia::TPatriciaTrie::Insert(key, number);
        }
        else if(action == "-"){
            std::cin >> key;
            ToLowerCase(key);
            if (pt->Delete(key))
                std::cout << "OK\n";
            else
               std::cout << "NoSuchWord\n";
        }
        else if (action == "!"){
            std::cin >> action;
            if (action == "Save"){
                std::string filename;
                std::cin >> filename;
                SaveLoad sl(filename);
                if (sl.Save(pt))
                    std::cout<<"OK\n";
                else{
                    std::cout << "ERROR: saving was not successful\n";
                }
            }
            else if (action == "Load"){
                pt->RecurseDestroy(pt->header);
                std::string filename;
                std::cin >> filename;
                SaveLoad sl(filename);
                nPatricia::TPatriciaTrie* ptTemp = new nPatricia::TPatriciaTrie;
                if (sl.Load(ptTemp)){
                    std::swap(ptTemp, pt);
                    std::cout << "OK\n";
                }
                else
                    std::cout << "ERROR: failed to upload file";
                ptTemp->RecurseDestroy(ptTemp->header->left);
                delete ptTemp->header;
            }
            else{
                std::cout << "ERROR: No such action\n";
            }
        }
        
    }
    return 0;
}
#include <iostream>
#include <cstring>
#include <fstream>

namespace nString {

    class tString{
    private:
        char *str;
        int len;
        static const int CINLIM = 2049;

    public:
        tString(){
            len = 0;
            str = new char[1];
            str[0] = '\0';
            std::cout << "[01] LOG MAKE EMPTY STRING\n";

        } //конструктор
        tString(const char *s) {
            len = std::strlen(s);
            str = new char [len + 1];
            std::strcpy(str,s);
        }//Конструктор по умлолчанию
        tString(const tString & s){
            len = s.len;
            str = new char [len];
            std::strcpy(str, s.str);
        } // конструктор копирования
        tString& operator=(const tString & s){
            if (this == &s)
                return *this;
            std::cout << "[1] LOG: STRING ASSIGNED" << str <<'\n';
            delete [] str;
            len = s.len;
            str = new char [len + 1];
            std::strcpy(str, s.str);
            std::cout << "[2] LOG: STRING ASSIGNED" << str <<'\n';
            return *this;
        } // оператор присваивания 
        friend std::ostream & operator<<(std::ostream & os,const tString & st){
            os << st.str;
            return os;
        }
        friend std::istream & operator>>(std::istream & in, tString& st){
            in >> st.str;
            return in;
        }
        ~tString() {
            std::cout << "\"" << str << "\"object deleted, "<< '\n';
            delete [] str;
        } // деструктор
    };//class tString
} // nString namespace

namespace nDict {
    class mKeyAndValue{
    public:
        unsigned long long key;
        nString::tString str;

        mKeyAndValue(){
            this->key = 0;
            this->str = nString::tString();
            std::cout << "[5] LOG: Make empty key \n";
        }
        mKeyAndValue(const long long & k,const nString::tString & s){
            this->key = k;
            this->str = nString::tString(s);
            std::cout << "Create: key - "<< this->key << ", value - " << str <<'\n';
        }
        mKeyAndValue(const mKeyAndValue& mkv){
            this->key = mkv.key;
            this->str = mkv.str;
        }// конструктор копирования
        mKeyAndValue& operator=(const mKeyAndValue& el){
            key = el.key;
            str = el.str;
            return *this;
        }//оператор присваивания 
    };// class mKeyValue

    class mDict {
    private:
    public:
        int quantity;
        int capacity;
        mKeyAndValue* data;
        mDict(){
            capacity = 4;
            quantity = 0;
            data = new mKeyAndValue[4];
        }
        mDict(const long long & k,const nString::tString& s){
            capacity = 1;
            quantity = 1;
            data = new mKeyAndValue(k,s);
        }
        ~mDict(){
            std::cout << "[4] LOG: DICT DELETE \n";
            delete [] data;
        }
        
        void AddElement(const mKeyAndValue& el){
            if(capacity <= quantity){
                mKeyAndValue* temp = new mKeyAndValue[2 * capacity];
                
                for (size_t i = 0; i < quantity; i++){
                    temp[i] = data[i];
                }
                
                delete [] data;
                capacity *= 2;
                data = temp;
                std::cout << "[3] LOG: STRING CAPACITY INCREASE" << capacity <<'\n';  
            }
            data[quantity] = el;
            quantity += 1;
        }
    }; // class mDictd 
} // nDict namespace




int main(){
    std::cout << "START PROCCES\n";    
    unsigned long long key;
    std::cout << "START PROCCES 2\n";
    nString::tString str;
    std::cout << "START PROCCES 3\n";
    nDict::mKeyAndValue el;
    std::cout << "START PROCCES 4\n";
    nDict::mDict dict;
    std::cout << "START PROCCES 5\n";
    while (std::cin >> key >> str)
    {  
        el = nDict::mKeyAndValue(key,str);
        dict.AddElement(el);
    }
    
    for (int i = 0; i < 4; i++)
    {
        std::cout <<"Key: " << dict.data[i].key << " str:" << dict.data[i].str << '\n';
    }
    
    //std::cout << "Dict data 2 key:" << dict.data[2].key << " value:" <<dict.data[2].string <<'\n';
    return 0;
}
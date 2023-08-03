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
        static int STRING_COUNTER;

    public:
        tString(){
            len = 0;
            str = new char[1];
            str[0] = '\0';
            STRING_COUNTER += 1;

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
            delete [] str;
            len = s.len;
            str = new char [len + 1];
            std::strcpy(str, s.str);
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
        long long key;
        nString::tString str;

        mKeyAndValue(){
            this->key = 0;
            this->str = nString::tString();
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
            capacity = 1;
            quantity = 0;
            data = new mKeyAndValue[1];
        }
        mDict(const long long & k,const nString::tString& s){
            capacity = 1;
            quantity = 1;
            data = new mKeyAndValue(k,s);
        }
        ~mDict(){
            delete [] data;
        }
        
        void AddElement(mKeyAndValue el){
            if(capacity <= quantity){
                mKeyAndValue* temp = new mKeyAndValue[2 * capacity];
                
                for (size_t i = 0; i < quantity; i++){
                    temp[i] = data[i];
                }
                
                delete [] data;
                capacity *= 2;
                data = temp;
            }
            data[quantity] = el;
            quantity += 1;
        }
    }; // class mDictd 
} // nDict namespace




int main(){
    /*
    nString::tString str1("a");
    nString::tString str2("b");
    nString::tString str3("c");
    nString::tString str4("d");
    nString::tString str5("e");
    nString::tString str6("f");
    nString::tString str7("g");
    //nDict::mDict dict1;
    //nDict::mKeyAndValue el1(111,"fffff");
    //nDict::mKeyAndValue el2(112,"aaaaa");
    //dict1.AddElment(dict1, el1);
    //dict1.AddElment(dict1,el2);
    //std::cout <<"In dict first element: " << dict1.data[0].key << '\n' ;
    //std::cout <<"In dict second element: " << dict1.data[1].key << '\n' ;
    nDict::mKeyAndValue el1(1,str1);
    nDict::mKeyAndValue el2(2,str2);
    nDict::mKeyAndValue el3(3,str3);
    nDict::mKeyAndValue el4(4,str4);
    nDict::mKeyAndValue el5(5,str5);
    nDict::mKeyAndValue el6(6,str6);
    nDict::mKeyAndValue el7(7,str7);
    nDict::mDict dict;
    dict.AddElement(el1);  
    dict.AddElement(el2);
    dict.AddElement(el3);
    dict.AddElement(el4);
    dict.AddElement(el5);
    dict.AddElement(el6);
    dict.AddElement(el7);
    std::cout << "String: " << str1 << '\n';
    std::cout << "Dict data 0 key:" << dict.data[0].key << " value:" <<dict.data[0].str <<'\n';
    std::cout << "Dict data 1 key:" << dict.data[1].key << " value:" <<dict.data[1].str <<'\n'; 
    std::cout << "Dict data 2 key:" << dict.data[2].key << " value:" <<dict.data[2].str <<'\n';
    std::cout << "Dict data 3 key:" << dict.data[3].key << " value:" <<dict.data[3].str <<'\n';
    std::cout << "Dict data 4 key:" << dict.data[4].key << " value:" <<dict.data[4].str <<'\n';
    std::cout << "Dict data 5 key:" << dict.data[5].key << " value:" <<dict.data[5].str <<'\n';
    std::cout << "Dict data 6 key:" << dict.data[6].key << " value:" <<dict.data[6].str <<'\n';
    */
    long long key;
    nString::tString str;
    std::ofstream out;

    while (std::cin >> key >> str)
    {
        std::cout <<"Key: " << key << " str:" << str << '\n';
    }
    //std::cout << "Dict data 2 key:" << dict.data[2].key << " value:" <<dict.data[2].string <<'\n';
    return 0;
}
#pragma once
#include <string>

 namespace nKeyAndValue {
        class TKeyAndValue{
        public:
            unsigned long long key;
            std::string str;

            TKeyAndValue();
            TKeyAndValue(const unsigned long long & k,const std::string s);
            TKeyAndValue(const TKeyAndValue& mkv);// конструктор копирования
            TKeyAndValue& operator=(const TKeyAndValue& el);//оператор присваивания 
            bool operator<(const TKeyAndValue& other) const {
                return key < other.key;
            }   
        };// class mKeyValue

        class TDict {
        public:
            int size;
            int capacity;
            TKeyAndValue* data = nullptr;

            TDict();
            TDict(const int & n);
            ~TDict();
            
            void AddElement(const TKeyAndValue& el);
            int GetSize();
        }; // class TDictd 
    } // nKeyAndValue namespace
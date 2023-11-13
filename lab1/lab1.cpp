#include <iostream>
#include <cstring>
#include "KeyAndValue.hpp"
#include "sorting.hpp"


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    unsigned long long key;
    std::string str;
    nKeyAndValue::TKeyAndValue el;
    nKeyAndValue::TDict dict;
    unsigned long long maxKey = -1;
    while (std::cin >> key >> str)
    {
        el = {key,str};
        if (maxKey < key)
            maxKey = key;   
        
        dict.AddElement(el);
    }
    int dictSize = dict.GetSize();
    nSorting::RadixSort(dict,maxKey,dictSize);
    for (int i = 0; i < dictSize; i++)
    {
        std::cout << dict.data[i].key << '\t' <<dict.data[i].str << '\n';
    }
    return 0;
}  
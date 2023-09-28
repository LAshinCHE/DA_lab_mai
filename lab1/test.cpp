#include <iostream>
#include <cstring>
#include <chrono>
#include <algorithm>
#include "KeyAndValue.hpp"
#include "sorting.hpp"


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
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
    nKeyAndValue::TDict bubbleDict(dictSize);
    std::copy(&dict.data[0], &dict.data[dictSize], bubbleDict.data);

    auto startRadix = std::chrono::high_resolution_clock::now();
    nSorting::RadixSort(dict,maxKey,dictSize);
    auto stopRadix = std::chrono::high_resolution_clock::now();
    auto durationRadix = std::chrono::duration_cast<std::chrono::microseconds>(stopRadix - startRadix);

    // auto startBubbleSort = std::chrono::high_resolution_clock::now();
    // nSorting::BubbleSort(dict, dictSize);
    // auto stopBubbleSort = std::chrono::high_resolution_clock::now();
    // auto durationBubbleSort = std::chrono::duration_cast<std::chrono::microseconds>(stopBubbleSort - startBubbleSort);

    auto startStableSort = std::chrono::high_resolution_clock::now();
    std::stable_sort(&dict.data[0], &dict.data[dictSize]);
    auto stopStableSort = std::chrono::high_resolution_clock::now();
    auto durationStableSort = std::chrono::duration_cast<std::chrono::microseconds>(stopStableSort - startStableSort);

    std::cout << "Radix sort time: " << durationRadix.count() << " mcs " << '\n';
    std::cout << "Stable sort time: " << durationStableSort.count() << " mcs " << '\n';
    //std::cout << "Bubble sort time: " << durationBubbleSort.count() << " mcs " << '\n';



    return 0;
}  
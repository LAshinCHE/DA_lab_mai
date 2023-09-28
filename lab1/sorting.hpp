#pragma once
#include "KeyAndValue.hpp"


namespace nSorting
{
    void CountingSort(nKeyAndValue::TDict& d, nKeyAndValue::TDict& tempDict,const int& digit,const int& dictSize,const int& bitShift);
    void RadixSort(nKeyAndValue::TDict& d, const unsigned long long& maxKey,const int& dictSize);
    void BubbleSort(nKeyAndValue::TDict& d, const int& dictSize);
};

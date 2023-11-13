#include <iostream>
#include <string>
#include <vector>

void makeStringCorrectSize(std::string& str){
    uint64_t mask = 1;
    while (mask <= str.size()){
        mask = mask << 1;
    }
    while(mask != str.size()){
        str += "$";
    }
} 

std::vector<int> CountingSort(const std::string& str){
    std::vector<int> count('z',0); 
    uint32_t sz = str.size();
    std::vector<int> sorted(sz);
    for (size_t i = 0; i < sz; i++){
        count[str[i]] += 1;
    }
    for (size_t i = 1; i < count.size(); i++){
        count[i] = count[i-1] + count[i];
    }
    for (int i = sz - 1; i >= 0; i--){
        sorted[count[str[i]]- 1] = i;
        count[str[i]]--;
    }
    return sorted;    
}

std::vector<int> makeEqualClasses(std::vector<int> sorted, std::string str){
    uint32_t sz  = str.size();
    std::vector<int> ec(sz,0);
    for (int i = 1; i < sz; i++){
        if (str[sorted[i]] != str[sorted[i - 1]])
            ec[sorted[i]] = ec[sorted[i - 1]] + 1;  
        else
            ec[sorted[i]] = ec[sorted[i - 1]];
    }
    return ec;
}


void printVec(std::vector<int> v){
    for (size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}


void PrefixCountingSort(std::vector<int>& sorted, std::vector<int>& ec, const uint32_t&  sz,const uint32_t& degree){
    std::vector<int> count(sz,0);
    std::vector<int> tempSorted(sz);
    for (size_t i = 0; i < sz; i++)
        tempSorted[i] = (sorted[i] - (1<<(degree))) % sz;
    printVec(sorted);
    printVec(tempSorted);
    std::cout << "ec: ";
    printVec(ec);
    // массив перестановак отсортирован по второй части 
    // первую часть сортируем по классам эквивалентности
    for (size_t i = 0; i < sz; i++){
        count[ec[tempSorted[i]]] += 1;
    }
    for (size_t i = 1; i < count.size(); i++){
        count[i] = count[i-1] + count[i];
    }
    std::cout << "count: ";
    printVec(count);
    for (int i = sz - 1; i >= 0; i--){
        sorted[count[ec[tempSorted[i]]] - 1] = tempSorted[i];
        count[ec[tempSorted[i]]]--;
    }   
    std::cout << "sorted: ";    
    // пересчитываем классы эквивалентности
    std::vector<int> tempEC(sz, 0);
    uint32_t classNumebr = 0;
    for (size_t i = 1; i < sz; i++){
        int secondPart1 = (sorted[i] + (1<<degree)) % sz;
        int secondPart2 = (sorted[i - 1] + (1<<degree)) % sz;
        if (ec[sorted[i]] != ec[sorted[i-1]] || ec[secondPart1] != ec[secondPart2])
            classNumebr += 1;
        tempEC[sorted[i]] = classNumebr;
    }
    ec = tempEC;
    
    
    printVec(sorted);

}

std::vector<int> makeSuffixArray(const std::string& s){
    uint32_t  sz = s.size();
    std::vector<int> sorted = CountingSort(s);
    std::cout << "sorted: ";
    printVec(sorted);
    std::vector<int> ec = makeEqualClasses(sorted,s);
    std::cout << "ec: ";
    printVec(ec);
    for (size_t degree = 0; (1<<degree) <= sz; degree++){
        std::cout << std::endl;
        std::cout << "degree of two: " << degree << std::endl;
        PrefixCountingSort(sorted, ec, sz, degree);
    }
    
    return sorted;
    
    
}



int main(){

    std::string s  = "caba";
    makeStringCorrectSize(s);
    std::vector<int> res =  makeSuffixArray(s);
    for (size_t i = 0; i < res.size(); i++){
        std::cout << res[i] << " ";
    }
    
    return 0;
}
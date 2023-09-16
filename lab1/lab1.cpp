    #include <iostream>
    #include <cstring>

    namespace nDict {
        class TKeyAndValue{
        public:
            unsigned long long key;
            std::string str;

            TKeyAndValue(): key(0), str() {}
            TKeyAndValue(const unsigned long long & k,const std::string s):key(k),str(s){}
            TKeyAndValue(const TKeyAndValue& mkv):key(mkv.key),str(mkv.str){}// конструктор копирования
            TKeyAndValue& operator=(const TKeyAndValue& el){
                key = el.key;
                str = el.str;
                return *this;
            }//оператор присваивания 
        };// class mKeyValue

        class TDict {
        private:
        public:
            int size =  0;
            int capacity = 0;
            TKeyAndValue* data = nullptr;
            TDict(): capacity(125000), size(0){
                data = new TKeyAndValue[capacity];
            }
            TDict(const int & n): size(0), capacity(n){
                data = new TKeyAndValue[n];
            }
            ~TDict(){
                delete [] data;
            }
            
            void AddElement(const TKeyAndValue& el){
                if(capacity <= size){
                    TKeyAndValue* temp = new TKeyAndValue[2 * capacity];
                    std::copy(&data[0],&data[size],temp);
                    std::swap(temp,data);
                    capacity *= 2;
                    delete [] temp;
                }
                data[size] = el;
                size += 1;
            }
            int GetSize(){
                return size;
            }
        }; // class TDictd 
    } // nDict namespace

    void CountingSort(nDict::TDict& d, nDict::TDict& tempDict,const int& digit,const int& dictSize,const int& bitShift){
        const int bitMask = 256;
        int bitArray[bitMask]  = {0};
        int dataByte;

        for (int i = 0; i < dictSize; i++){
            dataByte =  (d.data[i].key >> bitShift) & (bitMask - 1);
            bitArray[dataByte] += 1; 
        }
        
        for (int i = 1; i < bitMask; i++)
            bitArray[i] = bitArray[i - 1] + bitArray[i];


        for (int i = dictSize - 1; i >= 0; i--){
            dataByte = (d.data[i].key >> bitShift) & (bitMask - 1);
            tempDict.data[bitArray[dataByte] - 1] = d.data[i];
            bitArray[dataByte] -= 1;
        }

    }

    void RadixSort(nDict::TDict& d, const unsigned long long& maxKey,const int& dictSize){
        nDict::TDict tempDict(dictSize); 
        for (int digit =  0 ; digit < 8 ; digit++){
            if ((digit & 1) == 0)
                CountingSort(d,tempDict,digit, dictSize,digit * 8);
            else
                CountingSort(tempDict,d,digit, dictSize,digit * 8);
        }
        
    }

    int main(){
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);
        unsigned long long key;
        std::string str;
        nDict::TKeyAndValue el;
        nDict::TDict dict;
        unsigned long long maxKey = -1;
        while (std::cin >> key >> str)
        {
            el = {key,str};
            if (maxKey < key)
                maxKey = key;
            
            dict.AddElement(el);
        }
        int dictSize = dict.GetSize();
        RadixSort(dict,maxKey,dictSize);
        for (int i = 0; i < dictSize; i++)
        {
            std::cout << dict.data[i].key << '\t' <<dict.data[i].str << '\n';
        }
        return 0;
    }  
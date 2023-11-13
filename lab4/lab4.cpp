    #include <iostream>
    #include <string>
    #include <vector>


    unsigned int min(const unsigned int& n1,const unsigned int& n2){
        return (n1 < n2) ? n1 : n2;
    }


    std::vector<int> ZFunction (const std::vector<char> vPatterText,const unsigned int stringSize){
        std::vector<int> zFunctionArray(stringSize,0);

        unsigned int leftCoordinateCoverage  = 0;
        unsigned int rightCoordinateCoverage = 0;

        zFunctionArray[0] = stringSize;
        for (unsigned int iter = 1; iter < stringSize; iter++){
            if (iter <=  rightCoordinateCoverage)
                zFunctionArray[iter] = min(rightCoordinateCoverage - iter +  1,zFunctionArray[iter - leftCoordinateCoverage]);
            while (iter +  zFunctionArray[iter] < stringSize && (
            vPatterText[zFunctionArray[iter]] == vPatterText[iter + zFunctionArray[iter]] ||
            vPatterText[zFunctionArray[iter]] - 'A' == vPatterText[zFunctionArray[iter] + iter] - 'a' ||
            vPatterText[zFunctionArray[iter]] - 'a' == vPatterText[zFunctionArray[iter] + iter] - 'A'))
                    zFunctionArray[iter]++;
            if (iter + zFunctionArray[iter] - 1 > rightCoordinateCoverage){
                leftCoordinateCoverage = iter;
                rightCoordinateCoverage = iter + zFunctionArray[iter] - 1;
            }
        }

        return zFunctionArray;
    } 

    void ReadPatternAndText(std::vector<char>& vPatternText,std::vector<char>& vPatterTextWithoutNewLine){
        char letter;
        bool isPattern = true;
        char previous;
        while ((letter = getchar()) != EOF){
            if (letter == '\n' && isPattern){
                letter =  '$';
                isPattern = false;
            }
            else if (letter == '\n' && !isPattern){
                vPatternText.push_back(letter);
                letter = ' ';
                vPatterTextWithoutNewLine.push_back(letter);
                previous = letter;
                continue;   
            }
            if ((previous == ' ' && letter == ' ') ||(previous == '$' && letter == ' '))
                continue;
            previous = letter;
            vPatternText.push_back(letter);
            vPatterTextWithoutNewLine.push_back(letter);
        }
        
    }

    std::vector<char> DeleteAllUslesSpacesAndCountPatternSize(std::vector<char>& vPatterTextWithoutNewLine,unsigned int& patternSize){
        std::vector<char> vPatternAndTextResult;
        char previous  = -1;
        bool isPattern = true;
        for (char letter : vPatterTextWithoutNewLine){
            if (previous == letter && letter == ' ')
                continue;
            if (letter == '$')
                isPattern = false;
            if (isPattern)
                patternSize += 1;
            
            vPatternAndTextResult.push_back(letter);
            previous = letter;
        }
        return vPatternAndTextResult;
    }


    void outputResult(const std::vector<int> zFunctionArray,const std::vector<char> vPatternText,const std::vector<char> vPatterTextResult,const int patternSize){
        long unsigned int i = patternSize;
        long unsigned int j = patternSize;
        int wordCouter = 1;
        int stringCouter = 1;
        while(i < vPatternText.size() && j < vPatterTextResult.size()){
            if (vPatterTextResult[j] == ' '){
                j += 1;
                continue;
            }
            if (vPatternText[i] != vPatterTextResult[j]){
                if (vPatternText[i] == ' '){
                    wordCouter += 1;
                    i += 1;
                    continue;
                }
                else if(vPatternText[i] == '\n'){
                    stringCouter += 1;
                    wordCouter = 1;
                    i += 1;
                    continue;
                }
            }
            if (vPatternText[i]  == ' '){
                wordCouter += 1;
                i += 1;
                j += 1;
                continue;
            }
            else if(vPatternText[i] == '\n'){
                stringCouter += 1;
                wordCouter = 1;
                i += 1;
                j += 1;
                continue;
            }
            if (zFunctionArray[j] == patternSize)
                std::cout << stringCouter << ", " << wordCouter << '\n';
            
            i +=1;
            j += 1;
        }
    }

    int main(){
        std::vector<char> vPatternText;
        std::vector<char> vPatternTextWithoutNewLine;

        ReadPatternAndText(vPatternText,vPatternTextWithoutNewLine);
        unsigned int patternSize = 0;

        std::vector<char>vPatterTextResult = DeleteAllUslesSpacesAndCountPatternSize(vPatternTextWithoutNewLine, patternSize);


        std::vector<int> zFunctionArray = ZFunction(vPatterTextResult,vPatterTextResult.size());
        
        outputResult(zFunctionArray,vPatternText,vPatterTextResult,patternSize);
        return 0;
    }
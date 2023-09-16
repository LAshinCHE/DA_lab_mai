#include <iostream>
#include <vector>

int min(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

std::vector<int> z_function(const std::vector<char> s, const int s_size){
    std::vector<int> z(s_size, 0);
    int l = 0;
    int r = 0;
    for (int i = 1; i < s_size; ++i){
        if (i <= r){
            z[i] = min(r + 1 - i, z[i - l]);
        }
        while (z[i] + i < s_size && s[z[i]] == s[z[i] + i]){
            z[i]++;
        }
        if (z[i] - 1 + i > r){
            l = i;
            r = z[i] - 1 + i;
        }
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::vector<char> v;
    std::vector<char> v_without_new_line;
    int c, pre_c;
    pre_c = -1;
    bool end_pattern = true;
    int count = 0;
    while ((c = getchar()) != EOF){//read pattern$text
        c = (unsigned char)tolower(c);
        if (c == ' '){
            c = '|';
        } else if (c == '\n' && end_pattern){
            c = '$';
            end_pattern = false;
        } else if (c == '\n' && !end_pattern){
            c = '/';
            v.push_back(c);
            c = '|';
            v_without_new_line.push_back(c);
            pre_c = c;
            continue;
        }
        if ((pre_c == c && c == '|') || (pre_c == '$' && c == '|')){
            continue;
        } else if (pre_c == -1 && c == '|'){
            continue;
        }
        pre_c = c;
        v_without_new_line.push_back(c);
        v.push_back(c);
    }
    std::vector<char> n_v;
    pre_c = -1;
    bool flag = true;
    for (char i : v_without_new_line){
        if (pre_c == i && i == '|')
            continue;
        if (i == '$')
            flag = false;
        if (flag)
            count++;
        n_v.push_back(i);
        pre_c = i;
    }
    std::vector<int> z_res = z_function(n_v, n_v.size());
    int line = 1;
    int word = 1;
    int i = count, j = count;
    while (i < v.size() && j < n_v.size()){
        if (n_v[j] == '|'){
            j++;
            continue;
        }
        if (v[i] != n_v[j]){
            if (v[i] == '|'){
                word++;
                i++;
                continue;
            } else if (v[i] == '/'){
                line++;
                word = 1;
                i++;
                continue;
            }
        }
        if (v[i] == '|'){
            word++;
            j++;
            i++;
            continue;
        } else if (v[i] == '/'){
            line++;
            word = 1;
            i++;
            j++;
            continue;
        }
        if (z_res[j] == count){
            std::cout << line << ',' << ' ' << word << std::endl;
        }
        i++;
        j++;
    }

    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

long long findA(const vector<int> &ops, long long result){
    if(ops.size() == 0) return result;
    long long a, b, c;
    for(int i = 0; i < 8; i++){
        a = result * 8;
        a += i;
        b = a % 8;
        b = b ^ 5;
        c = a / (1 << b);
        b = b ^ c;
        b = b ^ 6;
        if(b % 8 == ops.back()){
            vector<int> copy(ops.begin(), ops.end() - 1);
            long long r = findA(copy, a);
            if(r == -1) continue;
            return r;
        }
    }
    return -1;
}

int main(){
    int A, B, C;
    bool read = scanf("Register A: %d ", &A) == 1;
    read &= scanf("Register B: %d ", &B) == 1;
    read &= scanf("Register C: %d \n", &C) == 1;
    if(!read) return 1;
    
    string line;
    getline(cin, line);
    string prefix = "Program: ";
    line.erase(line.begin(), line.begin() + prefix.size());

    stringstream ss(line);
    vector<int> ops;
    string token;
    while(getline(ss, token, ',')){
        int num = token[0] - '0';
        ops.push_back(num);
    }

    cout << setprecision(20) << findA(ops, 0) << endl;
    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

int main(){
    string line;
    long long sum = 0;
    
    bool shouldMultiply = true;
    while(getline(cin, line)){
        while(line.size() != 0){
            
            char doInstruction[5];
            if(sscanf(line.c_str(), "%4s", doInstruction) == 1){
                if(strcmp(doInstruction, "do()") == 0){
                    shouldMultiply = true;
                }
            }
            
            char dontInstruction[8];
            if(sscanf(line.c_str(), "%7s", dontInstruction) == 1){
                if(strcmp(dontInstruction, "don't()") == 0){
                    shouldMultiply = false;
                }
            }

            int a, b;
            char c;
            if(sscanf(line.c_str(), "mul(%3d,%3d%c", &a, &b, &c) == 3 && shouldMultiply){
                if(c == ')') sum += (long long)a*b;
            }
            line.erase(line.begin());
        }
    }

    cout << sum << endl;

    return 0;
}
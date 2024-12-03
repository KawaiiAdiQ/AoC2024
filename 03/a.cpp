#include <bits/stdc++.h> 

using namespace std;

int main(){
    string line;
    long long sum = 0;
    
    while(getline(cin, line)){
        while(line.size() != 0){
            int a, b;
            char c;
            if(sscanf(line.c_str(), "mul(%3d,%3d%c", &a, &b, &c) == 3){
                if(c == ')') sum += (long long)a*b;
            }
            line.erase(line.begin());
        }
    }

    cout << sum << endl;

    return 0;
}
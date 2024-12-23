#include <bits/stdc++.h> 

using namespace std;

int main(){
    long long total = 0;
    long long secret;
    while(cin >> secret){
        for(int i = 0; i < 2000; i++){
            secret ^= secret * 64;
            secret %= 16777216;
            secret ^= secret / 32;
            secret %= 16777216;
            secret ^= secret * 2048;
            secret %= 16777216;
        }
        total += secret;
    }
    
    cout << total << endl;

    return 0;
}
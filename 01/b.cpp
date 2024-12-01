#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<int> l;
    vector<int> r;
    map<int, int> occur;

    int a, b;
    while(cin >> a >> b){
        l.push_back(a);
        if(occur.find(b) != occur.end())
            occur[b]++;
        else occur.insert({b, 1});
    }

    long long sum = 0;
    for(int x : l){
        if(occur.find(x) != occur.end())
            sum += (long long)x * occur[x];
    }

    cout << sum << endl;

    return 0;
}
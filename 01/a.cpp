#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<int> l;
    vector<int> r;

    int a, b;
    while(cin >> a >> b){
        l.push_back(a);
        r.push_back(b);
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    int sum = 0;
    for (size_t i = 0; i < l.size(); i++){
        sum += abs(l[i] - r[i]);
    }
    
    cout << sum << endl;

    return 0;
}
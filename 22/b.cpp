#include <bits/stdc++.h> 

using namespace std;

int main(){
    long long secret;
    vector<vector<int>> bananas;
    int lineID = 0;
    while(cin >> secret){
        bananas.push_back(vector<int>());
        bananas[lineID].push_back(secret % 10);
        
        for(int i = 0; i < 2000; i++){
            secret ^= secret * 64;
            secret %= 16777216;
            secret ^= secret / 32;
            secret %= 16777216;
            secret ^= secret * 2048;
            secret %= 16777216;
            bananas[lineID].push_back(secret % 10);
        }
        
        lineID++;
    }

    vector<vector<int>> diff;
    for(int i = 0; i < (int)bananas.size(); i++){
        diff.push_back(vector<int>());
        for(int j = 1; j < (int)bananas[0].size(); j++){
            diff[i].push_back(bananas[i][j] - bananas[i][j - 1]);
        }
    }

    map<string, int> seq_map;
    for(int i = 0; i < (int)diff.size(); i++){
        set<string> seen;
        for(int j = 0; j < (int)diff[i].size() - 4; ++j){
            string key = "";
            for(int k = 0; k < 4; k++){
                key += to_string(diff[i][j + k]);
            }
            if(seen.count(key)) continue;

            seen.insert(key);
            if(seq_map.count(key) == 0){
                seq_map.insert({ key, 0 });
            }
            seq_map[key] += bananas[i][j+4];
        }
        seen.clear();
    }

    int res = 0;
    for(auto [key, val] : seq_map){
        res = max(val, res);
    }

    cout << res << endl;

    return 0;
}
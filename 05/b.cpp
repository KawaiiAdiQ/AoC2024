#include <bits/stdc++.h> 

using namespace std;

bool areUpdatesValid(
    const map<int, set<int>> &rules,
    const vector<int> &updates
){
    vector<int> processed;
    for(int u : updates){
        if(rules.find(u) == rules.end()){
            processed.push_back(u);
            continue;
        }
        for(int p : processed){
            if(rules.at(u).find(p) != rules.at(u).end()){
                return false; 
            }
        }
        processed.push_back(u);
    }

    return true;
}

void fixUpdates(
    const map<int, set<int>> &rules,
    vector<int> &updates
){
    vector<int> processed;
    for(int u : updates){
        if(rules.find(u) == rules.end()){
            processed.push_back(u);
            continue;
        }

        bool prepended = false;
        for(auto it = processed.begin(); it != processed.end(); ++it){
            if(rules.at(u).find(*it) != rules.at(u).end()){
                processed.insert(it, u);
                prepended = true;
                break;
            }
        }
        if(!prepended) processed.push_back(u);
    }

    updates = processed;
}

int main(){
    map<int, set<int>> rules;

    int a, b;
    string line;
    while(getline(cin, line)){
        if(sscanf(line.c_str(), "%d|%d", &a, &b) == 2){
            if(rules.find(a) != rules.end()){
                rules[a].insert(b);
            }
            else{
                rules.insert({a, set<int>()});
                rules.at(a).insert(b);
            }
        }
        else break;
    }

    int sum = 0;
    while(getline(cin, line)){
        vector<int> updates;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')){
            updates.push_back(stoi(token));
        }
        if(!areUpdatesValid(rules, updates)){
            fixUpdates(rules, updates);
            sum += updates[updates.size() / 2];
        }
    }
    
    cout << sum << endl;

    return 0;
}
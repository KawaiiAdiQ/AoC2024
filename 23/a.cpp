#include <bits/stdc++.h> 

using namespace std;

int main(){
    map<string, set<string>> graph;
    set<string> tNodes;

    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        string from, to;
        getline(ss, from, '-');
        getline(ss, to, '-');
        graph[from].insert(to);
        graph[to].insert(from);
        if(from[0] == 't') tNodes.insert(from);
        if(to[0] == 't') tNodes.insert(to);
    }

    set<string> visited;
    for(string node : tNodes){
        for(string from : graph[node]){
            for(string to : graph[node]){
                if(from == to) continue;

                if(graph[from].find(to) != graph[from].end()){
                    vector<string> path = {from, node, to};
                    sort(path.begin(), path.end());
                    string hash;
                    for(string p : path) hash += p;
                    visited.insert(hash);
                }
            }
        }
    }

    cout << visited.size() << endl;

    return 0;
}
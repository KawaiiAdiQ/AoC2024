#include <bits/stdc++.h> 

using namespace std;

set<string> hashes;

void findCompleteGraphs(const map<string, set<string>> &graph, string node, vector<string> &nodes){
    string hash = "";
    sort(nodes.begin(), nodes.end());
    for(string n : nodes) hash += n + ',';
    if(hashes.find(hash) != hashes.end()) return;
    hashes.insert(hash);

    for(string neighbor : graph.at(node)){
        if(find(nodes.begin(), nodes.end(), neighbor) != nodes.end()) continue;
        bool complete = true;
        for(string n : nodes){
            if(graph.at(neighbor).find(n) == graph.at(neighbor).end()){
                complete = false;
                break;
            }
        }
        if(!complete) continue;
        vector<string> newNodes = nodes;
        newNodes.push_back(neighbor);
        findCompleteGraphs(graph, neighbor, newNodes);
    }
}

int main(){
    map<string, set<string>> graph;

    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        string from, to;
        getline(ss, from, '-');
        getline(ss, to, '-');
        graph[from].insert(to);
        graph[to].insert(from);
    }

    vector<string> res;
    for(auto [key, s] : graph){
        vector<string> nodes{ key };
        findCompleteGraphs(graph, key, nodes);
    }

    size_t longestSize = 0;
    string longestHash = "";
    for(string hash : hashes){
        if(hash.size() > longestSize){
            longestSize = hash.size();
            longestHash = hash;
        }
    }

    longestHash.resize(longestHash.size() - 1); // Remove trailing comma

    cout << longestHash << endl;

    return 0;
}
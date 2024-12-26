#include <bits/stdc++.h> 

using namespace std;

struct gate{
    string a, b, op, out;
};


int main(){
    map<string, int> states;
    string line;
    while(getline(cin, line)){
        if(line.size() < 4) break;
        string wire = line.substr(0, 3);
        int state = stoi(line.substr(5, 1));
        states[wire] = state;
    }

    set<string> wires;
    vector<gate> gates;
    while(getline(cin, line)){
        stringstream ss(line);
        string a, b, op, arrow, out;
        ss >> a >> op >> b >> arrow >> out;
        if(out[0] == 'z') wires.insert(out);
        gates.push_back(gate{a, b, op, out});
    }

    while(!gates.empty()){
        for(auto it = gates.begin(); it != gates.end();){
            gate g = *it;
            if(states.find(g.a) != states.end() && states.find(g.b) != states.end()){
                if(g.op == "AND"){
                    states[g.out] = states[g.a] & states[g.b];
                }
                if(g.op == "OR"){
                    states[g.out] = states[g.a] | states[g.b];
                }
                if(g.op == "XOR"){
                    states[g.out] = states[g.a] ^ states[g.b];
                }
                it = gates.erase(it);
            }
            else{
                it++;
            }
        }
    }

    long long result = 0;
    for(int i = 0; i < (int)wires.size(); i++){
        string out = "z" + to_string(i);
        if(out.size() == 2) out = "z0" + to_string(i);
        if(states.find(out) != states.end()){
            result |= ((long long)states[out] << i);
        }
    }

    cout << result << endl;

    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

struct gate{
    string a, b, op, out;

    bool hasEndWire(){
        return out[0] == 'z';
    }

    bool hasInputWires(){
        return (a[0] == 'x' || a[0] == 'y') && (b[0] == 'x' || b[0] == 'y');
    }

    bool hasLSB(){
        return a.substr(1) == "00" && b.substr(1) == "00";
    }
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

    string lastZ = "z" + to_string(wires.size() - 1);
    set<string> broken;
    for(gate g : gates){
        // https://cs.wikipedia.org/wiki/Bin%C3%A1rn%C3%AD_s%C4%8D%C3%ADta%C4%8Dka#/media/Soubor:Full_Adder_Modules.svg
        // z value must be from XOR gate
        if(g.hasEndWire() && g.op != "XOR" && g.out != lastZ) broken.insert(g.out);
        
        // non-input XOR non-input = non-out breaks the circuit
        if(!g.hasEndWire() && !g.hasInputWires() && g.op == "XOR") broken.insert(g.out);
        
        // input XOR input = out, then out must be in another XOR gate
        if(g.op == "XOR" && g.hasInputWires() && !g.hasLSB()){
            bool outInLaterXOR = false;
            for(gate g2 : gates){
                if(g2.op == "XOR" && (g2.a == g.out || g2.b == g.out)){
                    outInLaterXOR = true;
                    break;
                }
            }

            if(!outInLaterXOR) broken.insert(g.out);
        }

        // input AND input = out, then out must be in another OR gate
        if(g.op == "AND" && g.hasInputWires() && !g.hasLSB()){
            bool outInLaterOr = false;
            for(gate g2 : gates){
                if(g2.op == "OR" && (g2.a == g.out || g2.b == g.out)){
                    outInLaterOr = true;
                    break;
                }
            }

            if(!outInLaterOr) broken.insert(g.out);
        }
    }


    vector<string> brokenVec(broken.begin(), broken.end());
    sort(brokenVec.begin(), brokenVec.end());

    string result = "";
    for(string wire : brokenVec){
        result += wire + ",";
    }
    result.resize(result.size() - 1); // remove last comma

    cout << result << endl;

    return 0;
}
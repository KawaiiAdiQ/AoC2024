#include <bits/stdc++.h> 

using namespace std;

int A, B, C;
int ip = 0;
string res = "";

void adv(int operand){
    A = (int)(A / (1 << operand));
    ip += 2;
}

void bxl(int operand){
    B ^= operand;
    ip += 2;
}

void bst(int operand){
    B = operand % 8;
    ip += 2;
}

void jnz(int operand){
    if(A != 0) ip = operand;
    else ip += 2;
}

void bxc(int operand){
    B ^= C;
    operand++;
    ip += 2;
}

void out(int operand){
    res += to_string(operand % 8);
    res += ",";
    ip += 2;
}

void bdv(int operand){
    B = (int)(A / (1 << operand));
    ip += 2;
}

void cdv(int operand){
    C = (int)(A / (1 << operand));
    ip += 2;
}

int main(){
    bool read = scanf("Register A: %d ", &A) == 1;
    read &= scanf("Register B: %d ", &B) == 1;
    read &= scanf("Register C: %d \n", &C) == 1;
    if(!read) return 1;
    
    string line;
    getline(cin, line);
    string prefix = "Program: ";
    line.erase(line.begin(), line.begin() + prefix.size());

    stringstream ss(line);
    vector<int> ops;
    string token;
    while(getline(ss, token, ',')){
        int num = token[0] - '0';
        ops.push_back(num);
    }

    void (*instructions[8])(int) = { adv, bxl, bst, jnz, bxc, out, bdv, cdv };

    while(ip + 1 < (int)ops.size()){
        int opcode = ops[ip];
        int operand = ops[ip + 1];
        switch(operand){
            case 4:
                if(opcode != 1) instructions[opcode](A);
                else instructions[opcode](operand);
                break;
            case 5:
                if(opcode != 1) instructions[opcode](B);
                else instructions[opcode](operand);
                break;
            case 6:
                if(opcode != 1) instructions[opcode](C);
                else instructions[opcode](operand);
                break;
            default:
                instructions[opcode](operand);
                break;
        };
    }

    if(!res.empty()) res.pop_back();

    cout << res << endl;

    return 0;
}
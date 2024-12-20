#include <bits/stdc++.h> 

using namespace std;

map<string, long long> memo;

long long isSolvable(const set<string> &towels, string final){
    if(!memo.count(final)){
        if(final.size() == 0) return 1;
        
        long long res = 0;
        for(string s : towels){
            if(final.compare(0, s.size(), s) == 0){
                res += isSolvable(towels, final.substr(s.size()));
            }
        }

        memo[final] = res;
    }

    return memo[final];
}

string trim(const string &str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos || end == std::string::npos) {
        return ""; // String contains only whitespace
    }

    return str.substr(start, end - start + 1);
}

int main(){
    set<string> towels;

    string line;
    getline(cin, line);
    stringstream ss(line);

    string token;
    while(getline(ss, token, ',')){
        string trimmed = trim(token);
        towels.insert(trimmed);
    }

    getline(cin, line); // new line -> skip

    long long possibleWays = 0;
    while(getline(cin, line)){
        possibleWays += isSolvable(towels, line);
    }

    cout << possibleWays << endl;

    return 0;
}
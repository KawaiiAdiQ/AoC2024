#include <bits/stdc++.h> 

using namespace std;

map<pair<long long, int>, long long> memo;

long long solveRec(long long stone, int stepsLeft){
    if(stepsLeft == 0) return 1;

    pair<long long, int> state = {stone, stepsLeft};
    if (memo.find(state) != memo.end()) {
        return memo[state];
    }

    long long res = 0;
    string stoneStr = to_string(stone);
    if(stone == 0){
        res += solveRec(1, stepsLeft - 1);
    }
    else if(stoneStr.length() % 2 == 0){
        int mid = stoneStr.length() / 2;
        long long l = stoll(stoneStr.substr(0, mid));
        long long r = stoll(stoneStr.substr(mid));
        res += solveRec(l, stepsLeft - 1);
        res += solveRec(r, stepsLeft - 1);
    }
    else{
        res += solveRec(stone * 2024, stepsLeft - 1);
    }

    memo[state] = res;
    return res;
}

int main(){
    stack<long long> stones;
    int a;
    while(cin >> a){
        stones.push(a);
    }

    long long res = 0;
    while(!stones.empty()){
        res += solveRec(stones.top(), 75);
        stones.pop();
    }

    cout << res << endl;

    return 0;
}
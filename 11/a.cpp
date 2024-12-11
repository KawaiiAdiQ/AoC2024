#include <bits/stdc++.h> 

using namespace std;

int main(){
    stack<long long> stones;
    int a;
    while(cin >> a){
        stones.push(a);
    }

    for(int i = 0; i < 25; i++){
        stack<long long> newStones;
        while(!stones.empty()){
            long long stone = stones.top();
            string stoneStr = to_string(stone);

            if(stone == 0){
                newStones.push(1);
            }
            else if(stoneStr.length() % 2 == 0){
                int mid = stoneStr.length() / 2;
                long long l = stoll(stoneStr.substr(0, mid));
                long long r = stoll(stoneStr.substr(mid));
                newStones.push(l);
                newStones.push(r);
            }
            else{
                newStones.push(stone * 2024);
            }

            stones.pop();
        }

        stones = newStones;
    }

    cout << stones.size() << endl;

    return 0;
}
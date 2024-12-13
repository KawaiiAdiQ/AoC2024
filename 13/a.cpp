#include <bits/stdc++.h> 

using namespace std;

int main(){
    int ax, ay, bx, by, px, py;
    int res = 0;

    while(scanf(" Button A: X%d, Y%d ", &ax, &ay) == 2){
        int r1 = scanf(" Button B: X%d, Y%d ", &bx, &by);
        int r2 = scanf(" Prize: X=%d, Y=%d ", &px, &py);
        if(r1 != 2 || r2 !=2) break;

        vector<vector<pair<int, int>>> dp(100, vector<pair<int, int>>(100, {0, 0}));
        for(int i = 1; i < 100; i++){
            dp[0][i] = {ax * i, ay * i};
            dp[i][0] = {bx * i, by * i};
        }

        int min_cost = 401;
        for(int i = 1; i < 100; i++){
            for(int j = 1; j < 100; j++){
                dp[i][j] = { dp[i-1][j].first + bx, dp[i-1][j].second + by };

                if(dp[i][j] == make_pair(px, py) && min_cost > 3 * j + i){
                    min_cost = 3 * j + i;
                }
            }
        }

        res += (min_cost == 401) ? 0 : min_cost;
    }

    cout << res << endl;

    return 0;
}
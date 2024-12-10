#include <bits/stdc++.h> 

using namespace std;

int paths(
    const vector<vector<int>> &grid,
    const pair<int, int> start
){
    int w = (int)grid[0].size() - 1;
    int h = (int)grid.size() - 1;

    auto inBounds = [w, h](int x, int y) {
        return (0 <= x && x <= w) && (0 <= y && y <= h);
    };

    vector<pair<int, int>> dirs{
        {1, 0},     // down
        {-1, 0},    // up
        {0, 1},     // right
        {0, -1},    // left
    };

    set<pair<int, int>> reached;
    queue<pair<int, int>> discovered;
    discovered.push(start);
    vector<vector<bool>> visited(h+1, vector<bool>(w+1, 0));
    while(!discovered.empty()){
        auto top = discovered.front();
        visited[top.first][top.second] = true;
        for(auto dir : dirs){
            int idy = top.first + dir.first;
            int idx = top.second + dir.second;
            if(inBounds(idx, idy)){
                if(visited[idy][idx]) continue;
                if(grid[idy][idx] == grid[top.first][top.second] + 1){
                    if(grid[top.first][top.second] == 8 && grid[idy][idx] == 9){
                        reached.insert({idy, idx});
                    }
                    else{
                        discovered.push({idy, idx});
                    }
                }
            }
        }
        discovered.pop();
    }

    return (int)reached.size();
}

int main(){
    vector<vector<int>> grid;
    vector<pair<int, int>> zeros;
    string line;
    int lineID = 0;
    while(getline(cin, line)){
        int colID = 0;
        grid.push_back(vector<int>());
        for(char c : line){
            grid[lineID].push_back(c - '0');
            if(c - '0' == 0){
                zeros.push_back({lineID, colID});
            }
            colID++;
        }
        lineID++;
    }
    
    int res = 0;
    for(auto zero : zeros){
        res += paths(grid, zero);
    }

    cout << res << endl;

    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<string> grid;
    string line;
    while(getline(cin, line)){
        grid.push_back(line);
    }

    vector<pair<int, int>> dirs{
        {1, 0},     // down
        {-1, 0},    // up
        {0, 1},     // right
        {0, -1},    // left
    };

    int h = (int)grid.size();
    int w = (int)grid[0].size();

    auto inBounds = [w, h](int x, int y) {
        return (0 <= x && x < w) && (0 <= y && y < h);
    };

    int res = 0;
    vector<vector<bool>> visited(h, vector<bool>(w, 0));
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(visited[i][j]) continue;

            int perimeter = 0;
            int area = 0;

            char curr = grid[i][j];

            queue<pair<int, int>> q;
            q.push({i, j});
            visited[i][j] = true;

            while(!q.empty()){
                auto front = q.front();
                area++;
                for(auto dir : dirs){
                    int idy = front.first + dir.first;
                    int idx = front.second + dir.second;
                    if(inBounds(idx, idy)){
                        if(grid[idy][idx] == curr && !visited[idy][idx]){
                            visited[idy][idx] = true;
                            q.push({idy, idx});
                        }
                        else if(grid[idy][idx] != curr){
                            perimeter++;
                        }
                    }
                    else{
                        perimeter++;
                    }
                }
                q.pop();
            }
            res += area * perimeter;
        }
    }
    cout << res << endl;

    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

int countSides(vector<pair<int, int>> &borders){
    
    sort(borders.begin(), borders.end(), 
    [](const pair<int, int> &a, const pair<int, int> &b) 
    {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });

    int sides = 1;
    auto currBorder = borders[0];
    for(int i = 1; i < (int)borders.size(); i++){
        if(!(currBorder.first == borders[i].first && currBorder.second == borders[i].second - 1)){
            sides++;
        }
        currBorder = borders[i];
    }

    return sides;
}

int main(){
    vector<string> grid;
    string line;
    while(getline(cin, line)){
        grid.push_back(line);
    }

    const pair<int, int> UP{-1, 0};
    const pair<int, int> DOWN{1, 0};
    const pair<int, int> LEFT{0, -1};
    const pair<int, int> RIGHT{0, 1};

    vector<pair<int, int>> dirs{UP, DOWN, LEFT, RIGHT};

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

            int area = 0;
            vector<pair<int, int>> u, d, l, r;

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
                            if(dir == UP)         u.push_back({idy, idx});
                            else if(dir == DOWN)  d.push_back({idy, idx});
                            else if(dir == LEFT)  l.push_back({idx, idy});
                            else if(dir == RIGHT) r.push_back({idx, idy});
                        }
                    }
                    else{
                        if(dir == UP)         u.push_back({idy, idx});
                        else if(dir == DOWN)  d.push_back({idy, idx});
                        else if(dir == LEFT)  l.push_back({idx, idy});
                        else if(dir == RIGHT) r.push_back({idx, idy});
                    }
                }
                q.pop();
            }

            int sides = 0;
            sides += countSides(u);
            sides += countSides(d);
            sides += countSides(l);
            sides += countSides(r);

            res += area * sides;
        }
    }
    cout << res << endl;

    return 0;
}
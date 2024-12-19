#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

vector<pii> dirs{ UP, DOWN, LEFT, RIGHT };

int findPath(const vector<vector<char>> &grid, const int w, const int h){
    auto inBounds = [w, h](int x, int y) {
        return (0 <= x && x < w) && (0 <= y && y < h);
    };

    vector<vector<int>> seen(h, vector<int>(w, INT32_MAX));
    seen[0][0] = 0;

    queue<pii> q;
    q.push({0, 0});

    while(!q.empty()){
        pii front = q.front();
        q.pop();

        for(pii dir : dirs){
            int nx = front.second + dir.second;
            int ny = front.first + dir.first;
            if(!inBounds(nx, ny)) continue;
            if(grid[ny][nx] == '#') continue;

            if(seen[ny][nx] > seen[front.first][front.second] + 1){
                seen[ny][nx] = seen[front.first][front.second] + 1;
                q.push({ny, nx});
            }
        }
    }

    return seen[70][70];
}

int main(){
    int w = 71, h = 71;

    vector<vector<char>> grid(h, vector<char>(w, '.'));
    int x, y;
    int cnt = 0;
    while(scanf("%d,%d ", &x, &y) == 2 && cnt < 1024){
        grid[y][x] = '#';
        cnt++;
    }

    while(scanf("%d,%d ", &x, &y) == 2){
        grid[y][x] = '#';
        cnt++;
        int res = findPath(grid, w, h);
        if(res == INT32_MAX){
            cout << x << ',' << y << endl;
            return 0;
        }
    }

    return 0;
}
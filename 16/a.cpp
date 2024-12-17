#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

struct node{
    int y, x;
    pii prevDir;
};

int main(){
    vector<vector<char>> grid;
    string line;
    int lineID = 0, colID = 0;
    int sx = -1, sy = -1, ex = -1, ey = -1;
    while(getline(cin, line)){
        grid.push_back(vector<char>());
        stringstream ss(line);
        char c;
        while(ss >> c){
            if(c == 'S'){
                sy = lineID;
                sx = colID;
            }
            if(c == 'E'){
                ey = lineID;
                ex = colID;
            }
            grid[lineID].push_back(c);
            colID++;
        }
        lineID++;
        colID = 0;
    }

    vector<vector<int>> cost(grid.size(), vector<int>(grid[0].size(), INT32_MAX));
    cost[sy][sx] = 0;

    vector<pii> dirs{ UP, DOWN, LEFT, RIGHT };
    
    queue<node> q;
    q.push(node{sy, sx, RIGHT});
    
    while(!q.empty()){
        node front = q.front();
        q.pop();

        if(make_pair(front.y, front.x) == make_pair(ey, ex)){
            continue;
        }

        for(auto dir : dirs){
            int ny = front.y + dir.first;
            int nx = front.x + dir.second;

            int c = (front.prevDir == dir) ? 1 : 1001;
            int currPathCost = cost[front.y][front.x] + c;
            if(grid[ny][nx] != '#' && cost[ny][nx] > currPathCost){
                cost[ny][nx] = currPathCost;
                q.push(node{ny, nx, dir});
            }
        }
    }

    cout << cost[ey][ex] << endl;

    return 0;
}
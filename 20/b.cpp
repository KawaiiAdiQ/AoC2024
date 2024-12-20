#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

vector<pii> dirs{ UP, DOWN, LEFT, RIGHT };

struct node{
    int y, x, cost;
};

int main(){
    int sx = -1, sy = -1, ex = -1, ey = -1;
    string line;
    vector<vector<char>> grid;
    int lineID = 0;
    while(getline(cin, line)){
        grid.push_back(vector<char>());
        stringstream ss(line);
        char c;
        int colID = 0;
        while(ss >> c){
            if(c == 'S'){
                sx = colID;
                sy = lineID;
            }
            if(c == 'E'){
                ex = colID;
                ey = lineID;
            }
            grid[lineID].push_back(c);
            colID++;
        }
        lineID++;
    }

    int currCost = 0;
    vector<node> path;
    path.push_back(node{sy, sx, currCost});
    set<pii> seen;

    while(!(sx == ex && sy == ey)){
        seen.insert({sy, sx});
        for(pii dir : dirs){
            int nx = sx + dir.second;
            int ny = sy + dir.first;
            if(grid[ny][nx] != '#' && seen.count({ny, nx}) == 0){
                sx = nx;
                sy = ny;
                path.push_back(node{sy, sx, ++currCost});
                break;
            }
        }
    }

    int saves = 0;
    for(int i = 0; i < (int)path.size(); i++){
        for(int j = i+1; j < (int)path.size(); j++){
            int dx = abs(path[i].x - path[j].x);
            int dy = abs(path[i].y - path[j].y);
            if(dx + dy <= 20){
                int cost = abs(path[i].cost - path[j].cost) - (dx + dy);
                if(cost >= 100){
                    saves++;
                }
            }
        }
    }

    cout << saves << endl;

    return 0;
}
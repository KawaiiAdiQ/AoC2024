#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

vector<pii> dirs{ UP, DOWN, LEFT, RIGHT };


struct node{
    int y, x;
    pii prevDir;
};

void printGrid(const std::vector<std::vector<int>>& grid) {
    if (grid.empty()) {
        std::cout << "The grid is empty." << std::endl;
        return;
    }

    // Find the maximum width of any number for formatting
    int maxWidth = 0;
    for (const auto& row : grid) {
        for (int num : row) {
            maxWidth = std::max(maxWidth, static_cast<int>(std::to_string(num).length()));
        }
    }

    // Print the grid as a table
    for (const auto& row : grid) {
        for (int num : row) {
            std::cout << std::setw(maxWidth + 2) << num; // +2 for padding
        }
        std::cout << std::endl;
    }
}

void findPathToZero(const vector<vector<int>> &cost, const int ey, const int ex, set<pii> &seen){
    queue<pii> qb;
    qb.push({ ey, ex });
    int prevCost = INT32_MAX;
    bool foundZero = false;
    set<pii> seenCurrently;

    while(!qb.empty()){
        pii front = qb.front();
        qb.pop();

        seenCurrently.insert(front);

        int currCost = cost[front.first][front.second];
        if(currCost == 0){
            foundZero = true;
            break;
        }

        for(pii dir : dirs){
            int ny = front.first + dir.first;
            int nx = front.second + dir.second;
            if(currCost - cost[ny][nx] == 1 || currCost - cost[ny][nx] == 1001){
                qb.push({ny, nx});
            }
            else if(cost[ny][nx] == prevCost - 2){
                findPathToZero(cost, ny, nx, seen);
            }
        }

        prevCost = currCost;
    }

    if(foundZero){
        for(pii s : seenCurrently){
            seen.insert(s);
        }
    }
}

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

    
    stack<node> q;
    q.push(node{sy, sx, RIGHT});
    
    while(!q.empty()){
        node front = q.top();
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

    //printGrid(cost);

    set<pii> seen;
    findPathToZero(cost, ey, ex, seen);

    cout << seen.size() << endl;

    return 0;
}
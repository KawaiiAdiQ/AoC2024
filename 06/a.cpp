#include <bits/stdc++.h> 

using namespace std;

void travel(vector<vector<char>> &grid, int x, int y){
    const vector<pair<int, int>> dirs {
        {0, -1},    // up
        {1, 0},     // right
        {0, 1},     // down
        {-1, 0},    // left
    };              // order is important

    int w = (int)grid[0].size() - 1;
    int h = (int)grid.size() - 1;

    int currDirID = 0;
    while(true){
        int nextX = x + dirs[currDirID].first;
        int nextY = y + dirs[currDirID].second;
        if(nextX < 0 || nextX > w || nextY < 0 || nextY > h)
            break;
        if(grid[nextY][nextX] == '#'){
            currDirID = (currDirID + 1) % 4;
        }
        else{
            grid[nextY][nextX] = 'X';
            x = nextX;
            y = nextY;
        }
    }
}

int countX(const vector<vector<char>> &grid){
    int count = 0;
    for(auto line : grid){
        for(char c : line){
            if(c == 'X') count++;
        }
    }
    return count;
}

int main(){
    vector<vector<char>> grid(1, vector<char>());
    char c;
    int lineID = 0, colID = 0;
    int x = 0, y = 0;
    while(cin.get(c)){
        if(c == '\n'){
            grid.push_back(vector<char>());
            lineID++;
            colID = 0;
        }
        else if(c == '^'){
            y = lineID;
            x = colID;
            grid[lineID].push_back('X');
        }
        else{
            grid[lineID].push_back(c);
            colID++;
        }
    }

    travel(grid, x, y);

    cout << countX(grid) << endl;

    return 0;
}
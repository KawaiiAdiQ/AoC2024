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

struct record{
    pair<int, int> border;
    pair<int, int> pos;

    bool operator == (record r){
        return r.border == border && r.pos == pos;
    }
};

bool loops(const vector<vector<char>> &grid, int x, int y){
    const vector<pair<int, int>> dirs {
        {0, -1},    // up
        {1, 0},     // right
        {0, 1},     // down
        {-1, 0},    // left
    };              // order is important

    int w = (int)grid[0].size() - 1;
    int h = (int)grid.size() - 1;

    vector<record> records;
    int currDirID = 0;
    while(true){
        int nextX = x + dirs[currDirID].first;
        int nextY = y + dirs[currDirID].second;
        if(nextX < 0 || nextX > w || nextY < 0 || nextY > h)
            return false;
        if(grid[nextY][nextX] == '#'){
            record r{{nextY, nextX}, {y, x}};
            auto it = find(records.begin(), records.end(), r);
            if(it != records.end())
                return true;
            records.push_back(r);
            currDirID = (currDirID + 1) % 4;
        }
        else{
            x = nextX;
            y = nextY;
        }
    }
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

    int count = 0;
    for(int i = 0; i < (int)grid.size(); i++){
        for(int j = 0; j < (int)grid[0].size(); j++){
            if(grid[i][j] == 'X'){
                vector<vector<char>> copy = grid;
                copy[i][j] = '#';
                if(loops(copy, x, y)) count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}
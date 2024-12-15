#include <bits/stdc++.h> 

using namespace std;

void printGrid(const vector<vector<char>> &grid){
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[0].size(); j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void moveRobot(
    vector<vector<char>> &grid, 
    pair<int, int> &robotPos,
    const pair<int, int> &dir
){
    int nx = robotPos.second + dir.second;
    int ny = robotPos.first + dir.first;
    
    if(grid[ny][nx] == '.'){
        grid[ny][nx] = '@';
        grid[robotPos.first][robotPos.second] = '.';
        robotPos.first = ny;
        robotPos.second = nx;
    }
    else if(grid[ny][nx] == 'O'){
        int nny = ny + dir.first;
        int nnx = nx + dir.second;
        while(grid[nny][nnx] != '.'){
            if(grid[nny][nnx] == '#') return;
            nny += dir.first;
            nnx += dir.second;
        }

        while(nnx != nx){
            grid[robotPos.first][nnx] = 'O';
            nnx -= dir.second;
        }
        
        while(nny != ny){
            grid[nny][robotPos.second] = 'O';
            nny -= dir.first;
        }

        grid[robotPos.first][robotPos.second] = '.';
        grid[ny][nx] = '@';
        robotPos.first = ny;
        robotPos.second = nx;
    }

    // printGrid(grid);
}

long long getSum(vector<vector<char>> &grid){
    long long sum = 0;
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[0].size(); j++){
            if(grid[i][j] == 'O'){
                sum += i * 100 + j;
            }
        }
    }

    return sum;
}

int main(){
    vector<vector<char>> grid;
    string line;
    int lineID = 0, colID = 0;
    int rx = 0, ry = 0;
    while(getline(cin, line)){
        if(line[0] != '#') break;

        grid.push_back(vector<char>());
        for(char c : line){
            if(c == '@'){
                rx = colID;
                ry = lineID;
            }
            grid[lineID].push_back(c);
            colID++;
        }
        
        lineID++;
        colID = 0;
    }

    pair<int, int> robotPos{ry, rx};
    while(getline(cin, line)){
        for(char c : line){
            switch(c){
                case '<': 
                    moveRobot(grid, robotPos, {0, -1});
                    break;
                case '^': 
                    moveRobot(grid, robotPos, {-1, 0});
                    break;
                case '>': 
                    moveRobot(grid, robotPos, {0, 1});
                    break;
                case 'v': 
                    moveRobot(grid, robotPos, {1, 0});
                    break;
            }
        }
    }

    cout << getSum(grid) << endl;

    return 0;
}
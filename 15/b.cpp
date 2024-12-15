#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

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
        return;
    }

    bool horizontal = (dir == LEFT || dir == RIGHT);
    bool movable = grid[ny][nx] == '[' || grid[ny][nx] == ']';

    if(movable && horizontal){
        int nnx = nx + 2 * dir.second;
        while(grid[ny][nnx] != '.'){
            if(grid[ny][nnx] == '#') return;
            nnx += 2 * dir.second;
        }

        while(nnx != nx){
            if(dir == LEFT){
                grid[robotPos.first][nnx] = '[';
                grid[robotPos.first][nnx+1] = ']';
            }
            if(dir == RIGHT){
                grid[robotPos.first][nnx] = ']';
                grid[robotPos.first][nnx-1] = '[';
            }
            nnx -= 2 * dir.second;
        }
        
        grid[robotPos.first][robotPos.second] = '.';
        grid[ny][nx] = '@';
        robotPos.first = ny;
        robotPos.second = nx;
        return;
    }

    if(movable && !horizontal){
        queue<pii> q;
        if(grid[ny][nx] == '['){
            q.push({ny, nx});
        }
        else q.push({ny, nx-1});

        vector<pii> discovered;
        while(!q.empty()){
            pii front = q.front();
            q.pop();
            
            if(find(discovered.begin(), discovered.end(), front) != discovered.end()) 
                continue;
            
            discovered.push_back(front);
            int nny = front.first + dir.first;

            if( grid[nny][front.second] == '#' || 
                grid[nny][front.second + 1] == '#'
            ) return;

            if(grid[nny][front.second] == '['){
                q.push({nny, front.second});
            }
            else if(grid[nny][front.second] == ']'){
                q.push({nny, front.second - 1});
            }

            if(grid[nny][front.second + 1] == '['){
                q.push({nny, front.second + 1});
            }

        }

        reverse(discovered.begin(), discovered.end());

        for(size_t i = 0; i < discovered.size() - 1; i++){
            if(discovered[i] == discovered[i+1]){
                discovered.erase(discovered.begin() + i + 1);
                i--;
            }
        }

        for(pii v : discovered){
            int yNew = v.first + dir.first;
            grid[yNew][v.second] = grid[v.first][v.second];
            grid[yNew][v.second+1] = grid[v.first][v.second+1];
            grid[v.first][v.second] = '.';
            grid[v.first][v.second+1] = '.';
        }

        grid[robotPos.first][robotPos.second] = '.';
        grid[ny][nx] = '@';
        robotPos.first = ny;
        robotPos.second = nx;
    }
}

long long getSum(vector<vector<char>> &grid){
    long long sum = 0;
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[0].size(); j++){
            if(grid[i][j] == '['){
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
                grid[lineID].push_back(c);
                grid[lineID].push_back('.');
            }
            else if(c == '#'){
                grid[lineID].push_back(c);
                grid[lineID].push_back(c);
            }
            else if(c == 'O'){
                grid[lineID].push_back('[');
                grid[lineID].push_back(']');
            }
            else{
                grid[lineID].push_back('.');
                grid[lineID].push_back('.');
            }
            colID += 2;
        }
        
        lineID++;
        colID = 0;
    }

    pair<int, int> robotPos{ry, rx};
    while(getline(cin, line)){
        for(char c : line){
            switch(c){
                case '<': 
                    moveRobot(grid, robotPos, LEFT);
                    break;
                case '^': 
                    moveRobot(grid, robotPos, UP);
                    break;
                case '>': 
                    moveRobot(grid, robotPos, RIGHT);
                    break;
                case 'v': 
                    moveRobot(grid, robotPos, DOWN);
                    break;
            }
        }
    }

    printGrid(grid);

    cout << getSum(grid) << endl;

    return 0;
}
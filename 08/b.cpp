#include <bits/stdc++.h> 

using namespace std;

void findAntinodes(
    const map<char, vector<pair<int, int>>> &antenas,
    vector<vector<char>> &grid
){
    int w = (int)grid[0].size() - 1;
    int h = (int)grid.size() - 1;

    auto inBounds = [w, h](int x, int y) {
        return (0 <= x && x <= w) && (0 <= y && y <= h);
    };

    for(const auto& [key, val] : antenas){
        for(int i = 0; i < (int)val.size(); i++){
            grid[val[i].second][val[i].first] = '#';
            for(int j = i+1; j < (int)val.size(); j++){
                int vx = val[i].first - val[j].first;
                int vy = val[i].second - val[j].second;

                int px1 = val[i].first + vx;
                int py1 = val[i].second + vy;

                while(inBounds(px1, py1)){
                    grid[py1][px1] = '#';
                    px1 += vx;
                    py1 += vy;
                }

                int px2 = val[j].first - vx;
                int py2 = val[j].second - vy;

                while(inBounds(px2, py2)){
                    grid[py2][px2] = '#';
                    px2 -= vx;
                    py2 -= vy;
                }
            }
        }
    }
}

int countAntinodes(const vector<vector<char>> &grid){
    int count = 0;
    for(auto line : grid){
        for(char c : line){
            if(c == '#') count++;
        }
    }
    return count;
}

int main(){
    map<char, vector<pair<int, int>>> antenas;
    vector<vector<char>> grid;
    string line;
    int lineID = 0, colID = 0;
    while(getline(cin, line)){
        grid.push_back(vector<char>());
        stringstream ss(line);
        char c;
        while(ss >> c){
            grid[lineID].push_back(c);
            if(c != '.'){
                if(antenas.count(c)){
                    antenas.at(c).push_back({colID, lineID});
                }
                else{
                    antenas.insert({c, vector<pair<int, int>>(1, {colID, lineID})});
                }
            }
            colID++;
        }
        lineID++;
        colID = 0;
    }

    findAntinodes(antenas, grid);

    cout << countAntinodes(grid) << endl;

    return 0;
}
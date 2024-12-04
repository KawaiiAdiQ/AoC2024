#include <bits/stdc++.h> 

using namespace std;

int findXMAS(const vector<vector<char>> &input, size_t i, size_t j){
    int count = 0;
    vector<pair<int, int>> dirs{
        {1, 0}, // down
        {-1, 0}, // up
        {0, 1}, // right
        {0, -1}, // left
        {1, 1}, // down right
        {1, -1}, // down left
        {-1, 1}, // up right
        {-1, -1}, // up left
    };

    for(auto dir : dirs){
        int Mx = i + dir.first;
        int My = j + dir.second;
        int Ax = i + 2 * dir.first;
        int Ay = j + 2 * dir.second;
        int Sx = i + 3 * dir.first;
        int Sy = j + 3 * dir.second;
        if(Mx < 0 || My < 0 || Ax < 0 || Ay < 0 || Sx < 0 || Sy < 0) continue;

        int w = (int)input.size() - 1;
        int h = (int)input[0].size() - 1;
        if(Mx > w || My > h || Ax > w || Ay > h || Sx > w || Sy > h) continue;
        
        if(input[Mx][My] == 'M' && input[Ax][Ay] == 'A' && input[Sx][Sy] == 'S') count++;
    }

    return count;
}

int main(){
    vector<vector<char>> input(1, vector<char>());
    int lineID = 0;
    char c;
    while(cin.get(c)){
        if(c == '\n'){
            lineID++;
            input.push_back(vector<char>());
        }
        else{
            input[lineID].push_back(c);
        }
    }

    int count = 0;
    for(size_t i = 0; i < input.size(); i++){
        for(size_t j = 0; j < input[i].size(); j++){
            if(input[i][j] == 'X'){
                count += findXMAS(input, i, j);
            }
        }
    }

    cout << count << endl;

    return 0;
}
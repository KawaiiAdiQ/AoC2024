#include <bits/stdc++.h> 

using namespace std;

int findMAS(const vector<vector<char>> &input, size_t i, size_t j){
    vector<pair<int, int>> dirs{
        {1, 1}, // down right
        {1, -1}, // down left
        {-1, 1}, // up right
        {-1, -1}, // up left
    };

    int matches = 0;
    for(auto dir : dirs){
        int Mx = i + dir.first;
        int My = j + dir.second;
        int Sx = i - dir.first;
        int Sy = j - dir.second;
        if(Mx < 0 || My < 0 || Sx < 0 || Sy < 0) continue;

        int w = (int)input.size() - 1;
        int h = (int)input[0].size() - 1;
        if(Mx > w || My > h || Sx > w || Sy > h) continue;
        
        if(input[Mx][My] == 'M' && input[Sx][Sy] == 'S') matches++;
    }

    return matches == 2 ? 1 : 0;
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
            if(input[i][j] == 'A'){
                count += findMAS(input, i, j);
            }
        }
    }

    cout << count << endl;

    return 0;
}
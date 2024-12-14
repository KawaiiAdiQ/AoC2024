#include <bits/stdc++.h> 

using namespace std;

struct robot{
    int px, py, vx, vy;
};

void printSpace(const vector<vector<int>> &space){
    for(auto line : space){
        for(int i : line){
            if(i == 0) cout << " ";
            else cout << "#";
        }
        cout << endl;
    }
}

bool hasLongLine(const vector<vector<int>> &space){
    for(auto row : space){
        string line = "";
        for(int i : row){
            if(i == 0) line += " ";
            else line += "#";
        }
        if(line.find("#################") != string::npos)
            return true;
    }

    return false;
}

int main(){
    int w = 101;
    int h = 103;
    vector<robot> robots;

    int px, py, vx, vy;
    while(scanf("p=%d,%d v=%d,%d ", &px, &py, &vx, &vy) == 4){
        robot r{ px, py, vx, vy };
        robots.push_back(r);
    }

    int seconds = 0;
    while(seconds < 10000){
        vector<vector<int>> space(h, vector<int>(w, 0));

        for(robot r : robots){
            int x = (r.px + seconds * r.vx) % w;
            if(x < 0) x += w;
            int y = (r.py + seconds * r.vy) % h;
            if(y < 0) y += h;
            space[y][x]++;
        }

        if(hasLongLine(space)){
            printSpace(space);
            cout << seconds << endl;
            break;
        }
        seconds++;
    }

    return 0;
}
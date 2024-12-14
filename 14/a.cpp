#include <bits/stdc++.h> 

using namespace std;

int main(){
    int seconds = 100;
    int w = 101;
    int h = 103;
    vector<vector<int>> space(h, vector<int>(w, 0));

    int px, py, vx, vy;
    while(scanf("p=%d,%d v=%d,%d ", &px, &py, &vx, &vy) == 4){
        int x = (px + seconds * vx) % w;
        if(x < 0) x += w;
        int y = (py + seconds * vy) % h;
        if(y < 0) y += h;
        space[y][x]++;
    }

    int q1=0, q2=0, q3=0, q4=0;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if(i < w/2 && j < h/2){
                q1 += space[j][i];
            }
            if(i < w/2 && j > h/2){
                q2 += space[j][i];
            }
            if(i > w/2 && j < h/2){
                q3 += space[j][i];
            }
            if(i > w/2 && j > h/2){
                q4 += space[j][i];
            }
        }
    }

    int res = q1 * q2 * q3 * q4;

    cout << res << endl;

    return 0;
}
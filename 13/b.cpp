#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

float norm(pair<ll, ll> xOld, pair<ll, ll> xNew){
    ll xSquared = (xOld.first - xNew.first) * (xOld.first - xNew.first);
    ll ySquared = (xOld.second - xNew.second) * (xOld.second - xNew.second);

    return sqrt(xSquared + ySquared);
}

void jacobi(const pair<ll, ll> A[2], pair<ll, ll> x, pair<ll, ll> b){
    // solve Ax=b

    pair<ll, ll> xNew = x;
    int iterCount = 0;
    
    do{
        xNew.first = (b.first/A[0].first) - (xNew.second * A[0].second / A[0].first);
        xNew.second = (b.second/A[1].second) - (xNew.first * A[1].first / A[1].second);
        iterCount++;
    } while(norm(x, xNew) > 1e-5 || iterCount < 150);

    x = xNew;
}

int main(){
    int ax, ay, bx, by, px, py;
    ll res = 0;

    while(scanf(" Button A: X%d, Y%d ", &ax, &ay) == 2){
        int r1 = scanf(" Button B: X%d, Y%d ", &bx, &by);
        int r2 = scanf(" Prize: X=%d, Y=%d ", &px, &py);
        if(r1 != 2 || r2 !=2) break;

        ll llpx = px + 10000000000000;
        ll llpy = py + 10000000000000;

        pair<ll, ll> A[2];
        A[0] = {(ll)ax, (ll)bx};
        A[1] = {(ll)ay, (ll)by};
        pair<ll, ll> x = { 0, 0 };
        pair<ll, ll> b = { llpx, llpy };

        GEM(A, x, b);
        cout << x.first << " " << x.second << endl;
    }

    cout << res << endl;

    return 0;
}
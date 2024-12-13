#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

void GEM(const double A[4], const double b[2], double x[2]){
    double factor = A[2] / A[0];
    double A3 = A[3] - factor * A[1];
    double b1 = b[1] - factor * b[0];

    x[1] = b1 / A3;
    x[0] = (b[0] - (A[1] * x[1])) / A[0];
}

int main(){
    double ax, ay, bx, by, px, py;
    ll res = 0;

    while(scanf(" Button A: X%lf, Y%lf ", &ax, &ay) == 2){
        int r1 = scanf(" Button B: X%lf, Y%lf ", &bx, &by);
        int r2 = scanf(" Prize: X=%lf, Y=%lf ", &px, &py);
        if(r1 != 2 || r2 != 2) break;

        px += 10000000000000;
        py += 10000000000000;

        double A[4] = { ax, bx, ay, by };
        double b[2] = { px, py };
        double x[2];

        GEM(A, b, x);

        bool xOK = b[0] == A[0] * round(x[0]) + A[1] * round(x[1]);
        bool yOK = b[1] == A[2] * round(x[0]) + A[3] * round(x[1]);

        if(xOK && yOK){
            res += x[0] * 3 + x[1];
        }
    }

    cout << res << endl;

    return 0;
}
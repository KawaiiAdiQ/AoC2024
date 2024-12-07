#include <bits/stdc++.h> 

using namespace std;

bool isPossible(long long goal, const vector<long long> &nums){
    vector<long long> partials(1, nums[0]);
    int startID = 0;
    int endID = 0;
    for(size_t level = 1; level < nums.size(); level++){
        while(startID <= endID){
            long long add = partials[startID] + nums[level];
            long long mul = partials[startID] * nums[level];
            long long cat = stoll(to_string(partials[startID]) + to_string(nums[level]));
            partials.push_back(add);
            partials.push_back(mul);
            partials.push_back(cat);
            startID++;
        }
        startID = endID + 1;
        endID += pow(3, level);
    }

    while(startID <= endID){
        if(partials[startID] == goal) return true;
        else startID++;
    }

    return false;
}

int main(){
    long long res = 0;
    string line;
    while(getline(cin, line)){
        long long goal;
        char separator;
        stringstream ss(line);
        ss >> goal >> separator;
        int num;
        vector<long long> nums;
        while(ss >> num){
            nums.push_back(num);
        }
        if(isPossible(goal, nums)){
            res += goal;
        }
    }

    cout << res << endl;

    return 0;
}
#include <bits/stdc++.h> 

using namespace std;

bool isOk(const vector<int> &numbers){
    bool ok = true;
    bool increasing = numbers[0] < numbers[1];
    for(size_t i = 1; i < numbers.size(); i++){
        int diff = abs(numbers[i-1] - numbers[i]);
        
        bool consistent = increasing 
            ? numbers[i-1] < numbers[i]
            : numbers[i-1] > numbers[i];
        
        if(diff < 1 || diff > 3 || !consistent){
            ok = false;
            break;
        }
    }

    return ok;
}

int main(){
    int safe = 0;
    string line;
    while(getline(cin, line)){
        vector<int> numbers;
        stringstream ss(line);
        int number;
        while(ss >> number){
            numbers.push_back(number);
        }
        
        if(isOk(numbers)) safe++;
        else{
            for(size_t i = 0; i < numbers.size(); i++){
                vector<int> copy(numbers);
                copy.erase(copy.begin() + i);
                if(isOk(copy)){
                    safe++;
                    break;
                }
            }
        }
    }

    cout << safe << endl;

    return 0;
}
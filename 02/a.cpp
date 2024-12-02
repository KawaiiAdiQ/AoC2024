#include <bits/stdc++.h> 

using namespace std;

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

        if(ok) safe++;
    }

    cout << safe << endl;

    return 0;
}
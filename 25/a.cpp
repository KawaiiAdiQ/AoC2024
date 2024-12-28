#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<vector<string>> objects;
    objects.push_back(vector<string>());

    string line;
    int objectIndex = 0;
    while(getline(cin, line)){
        if(line.size() <= 1){
            objects.push_back(vector<string>());
            objectIndex++;
        }
        else objects[objectIndex].push_back(line);
    }

    vector<vector<int>> locks, keys;
    for(vector<string> object : objects){
        vector<int> heights;

        if(object[0][0] == '.'){
            for(int i = 0; i < (int)object[0].size(); i++){
                int height = 0;
                for(int j = 0; j < (int)object.size(); j++){
                    if(object[j][i] == '.'){
                        height++;
                    }
                    else break;
                }
                heights.push_back(height);
            }
            locks.push_back(heights);
        }
        else{
            for(int i = 0; i < (int)object[0].size(); i++){
                int height = 0;
                for(int j = 0; j < (int)object.size(); j++){
                    if(object[j][i] == '#'){
                        height++;
                    }
                    else break;
                }
                heights.push_back(height);
            }
            keys.push_back(heights);
        }
    }

    int count = 0;
    for(auto lock : locks){
        for(auto key : keys){
            bool fit = true;
            for(int i = 0; i < (int)lock.size(); i++){
                if(lock[i] - key[i] < 0){
                    fit = false;
                    break;
                }
            }
            if(fit) count++;
        }
    }

    cout << count << endl;

    return 0;
}
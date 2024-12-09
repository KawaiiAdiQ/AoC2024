#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<int> files;
    stack<pair<int, int>> blocks;
    char digit;
    int read = 0;
    int fileID = 0;
    while(cin >> digit){
        int num = digit - '0';
        if(read % 2 == 0){
            for(int i = 0; i < num; i++){
                files.push_back(fileID);
                blocks.push({num, fileID});
            }
            read++;
            fileID++;
        }
        else{
            for(int i = 0; i < num; i++){
                files.push_back(-num);
            }
            read++;
        }
    }

    while(!blocks.empty()){
        auto block = blocks.top();
        for(int i = 0; i < (int)files.size(); i++){
            if(files[i] == block.second) break;
            if(-files[i] >= block.first){
                int free = -files[i];
                
                // rm previous
                for(int j = 0; j < (int)files.size(); j++){
                    if(files[j] == block.second)
                        files[j] = 0;
                }

                // replace
                for(int j = 0; j < block.first; j++){
                    files[i + j] = block.second;
                }

                // update hole
                for(int j = block.first; j < free; j++){
                    files[i + j] = -(free - block.first);
                }

                break;
            }
        }
        blocks.pop();
    }
    long long checksum = 0;
    for(int i = 0; i < (int)files.size(); i++){
        if(files[i] < 0) continue;
        checksum += (long long)files[i] * i;
    }

    cout << checksum << endl;

    return 0;
}
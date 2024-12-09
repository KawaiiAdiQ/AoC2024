#include <bits/stdc++.h> 

using namespace std;

int main(){
    vector<int> files;
    stack<int> blocks;
    char digit;
    int read = 0;
    int maxSize = 0;
    int fileID = 0;
    while(cin >> digit){
        int num = digit - '0';
        if(read % 2 == 0){
            for(int i = 0; i < num; i++){
                files.push_back(fileID);
                blocks.push(fileID);
            }
            read++;
            fileID++;
            maxSize += num;
        }
        else{
            for(int i = 0; i < num; i++){
                files.push_back(-1);
            }
            read++;
        }
    }

    for(int i = 0; i < maxSize; i++){
        if(files[i] == -1){
            files[i] =  blocks.top();
            blocks.pop();
        }
    }
    
    long long checksum = 0;
    for(int i = 0; i < maxSize; i++){
        checksum += (long long)files[i] * i;
    }

    cout << checksum << endl;

    return 0;
}
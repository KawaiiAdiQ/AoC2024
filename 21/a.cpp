#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> pii;

//
// GLOBALS
//

map<char, pii> numPadPos{
    { '7', {0, 0} },  { '8', {0, 1} }, { '9', {0, 2} }, 
    { '4', {1, 0} },  { '5', {1, 1} }, { '6', {1, 2} }, 
    { '1', {2, 0} },  { '2', {2, 1} }, { '3', {2, 2} }, 
                        { '0', {3, 1} }, { 'A', {3, 2} }
};

map<char, pii> arrowPadPos{
                        { '^', {0, 1} }, { 'A', {0, 2} }, 
    { '<', {1, 0} },  { 'v', {1, 1} }, { '>', {1, 2} }
};

pii RIGHT {0, 1};
pii LEFT {0, -1};
pii DOWN {1, 0};
pii UP {-1, 0};

vector<pii> dirs{ UP, DOWN, LEFT, RIGHT };

map<char, map<char, int>> numPadDist, arrowPadDist;

map<pair<char, char>, set<string>> shortestNumPadPaths, shortestArrowPadPaths;


//
// FUNCTIONS
//

map<char, map<char, int>> findDistances(
    map<char, pii> &pad, 
    const vector<char> &chars
){
    map<char, map<char, int>> distances;

    for(int i = 0; i < (int)chars.size(); i++){
        for(int j = 0; j < (int)chars.size(); j++){
            int dx = abs(pad[chars[i]].second - pad[chars[j]].second);
            int dy = abs(pad[chars[i]].first - pad[chars[j]].first);
            int dist = dx + dy;
            distances[chars[i]].insert({chars[j], dist});
            distances[chars[j]].insert({chars[i], dist});
        }
    }

    return distances;
}

char dirAsChar(pii dir){
    if(dir == UP) return '^';
    if(dir == DOWN) return 'v';
    if(dir == LEFT) return '<';
    if(dir == RIGHT) return '>';
    return ' ';
}

struct node{
    pii pos;
    string path;
    string seen;
};

set<string> findShortestPaths(const vector<string> &pad, char a, char b, bool isArrowPad = false){
    if(a == b) return {""};
    
    pii start = isArrowPad ? arrowPadPos[a] : numPadPos[a];
    pii end = isArrowPad ? arrowPadPos[b] : numPadPos[b];

    int w = pad[0].size();
    int h = pad.size();

    auto isValidPos = [w, h, pad](int y, int x) {
        return (0 <= x && x < w) && (0 <= y && y < h) && pad[y][x] != ' ';
    };

    auto visited = [](string seen, char c){
        return seen.find(c) != string::npos;
    };

    set<string> paths;
    queue<node> q;
    q.push(node{start, "", ""});

    while(!q.empty()){
        node currNode = q.front();
        q.pop();

        if(currNode.pos == end){
            if((int)currNode.path.size() == (isArrowPad ? arrowPadDist[a][b] : numPadDist[a][b]))
                paths.insert(currNode.path);
            continue;
        }

        for(auto dir : dirs){
            pii currPos = currNode.pos;
            pii nextPos = {currPos.first + dir.first, currPos.second + dir.second};
            if(isValidPos(nextPos.first, nextPos.second) && !visited(currNode.seen, pad[nextPos.first][nextPos.second])){
                q.push(node{nextPos, currNode.path + dirAsChar(dir), currNode.seen + pad[nextPos.first][nextPos.second]});
            }
        }
    }

    return paths;
}

long long findShortestSequence(string line, int depth, bool isArrowPad = false){
    map<pair<char, char>, set<string>> shortestPaths = isArrowPad ? shortestArrowPadPaths : shortestNumPadPaths;

    long long res = 0;

    line = 'A' + line;
    for(int i = 0; i < (int)line.size()-1; i++){
        char a = line[i];
        char b = line[i+1];

        if(depth == 0){
            res += arrowPadDist[a][b] +1;
            continue;
        }

        set<string> paths = shortestPaths[{a, b}];
        long long minDist = LLONG_MAX;
        for(string path : paths){
            path += "A";
            long long dist = findShortestSequence(path, depth-1, true);
            minDist = min(minDist, dist);
        }
        res += minDist;
    }

    return res;
}

int main(){
    vector<string> numPad{
        "789",
        "456",
        "123",
        " 0A"
    };

    vector<string> arrowPad{
        " ^A",
        "<v>"
    };

    vector<char> numPadChars{'A', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    numPadDist = findDistances(numPadPos, numPadChars);

    vector<char> arrowPadChars{'^', 'A', '<', 'v', '>'};
    arrowPadDist = findDistances(arrowPadPos, arrowPadChars);

    for(char a : numPadChars){
        for(char b : numPadChars){
            set<string> paths = findShortestPaths(numPad, a, b);
            shortestNumPadPaths[{a, b}] = paths;
        }
    }

    for(char a : arrowPadChars){
        for(char b : arrowPadChars){
            set<string> paths = findShortestPaths(arrowPad, a, b, true);
            shortestArrowPadPaths[{a, b}] = paths;
        }
    }

    long long sum = 0;
    string line;
    while(getline(cin, line)){
        long long p = findShortestSequence(line, 2);
        long long v = stoll(line.substr(0, line.size()-1));
        sum += v * p;
    }

    cout << sum << endl;

    return 0;
}
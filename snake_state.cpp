
#include "vlearn.h"

void State::setGridValue(Pos p, int val){
    grid[p.x][p.y] = val;
}

int State::getGridValue(Pos p){
    return grid[p.x][p.y];
}

State::State(){
    timer = 0;
    actionType = 0;
    snakes[0].size = 2;
    snakes[0].head = Pos(boardx/2, 1);
    snakes[0].tail = Pos(boardx/2, 0);

    snakes[1].size = 2;
    snakes[1].head = Pos(boardx/2, boardy-2);
    snakes[1].tail = Pos(boardx/2, boardy-1);
    
    for(int i=0; i<boardx; i++){
        for(int j=0; j<boardy; j++){
            grid[i][j] = -1;
        }
    }

    setGridValue(snakes[0].head, 4);
    setGridValue(snakes[0].tail, 0);
    setGridValue(snakes[1].head, 9);
    setGridValue(snakes[1].tail, 7);
    
    while(true){
        apple = Pos(rand() % boardx, rand() % boardy);
        if(validChanceAction(apple.x*boardy + apple.y)){
            break;
        }
    }
}

bool State::validAction(int action, int playerID){
    Pos nbr = snakes[playerID].head.shift(action);
    return nbr.inBounds() && (getGridValue(nbr) == -1);
}

void State::makeAction(double* reward){
    for(int i=0; i<numAgents; i++){
        assert(validAction(actions[i], i));
    }
    timer++;

    for(int i=0; i<numAgents; i++){
        Pos newHead = snakes[i].head.shift(actions[i]);
        setGridValue(snakes[i].head, actions[i] + 5*i);
        snakes[i].head = newHead;
        setGridValue(newHead, 4 + 5*i);
        if(newHead == apple){
            snakes[i].size ++;
            actionType = 1;
        }
        else{
            int tailDir = getGridValue(snakes[i].tail) - 5*i;
            setGridValue(snakes[i].tail, -1);
            snakes[i].tail = snakes[i].tail.shift(tailDir);
        }
    }

    if(actionType == 0) return;

    // compute rewards
    for(int i=0; i<numAgents; i++){
        reward[i] = 0;
    }
    for(int i=0; i<numAgents; i++){
        bool surrounded = true;
        for(int d=0; d<4; d++){
            if(validAction(d, i)){
                surrounded = false;
                break;
            }
        }
        if(surrounded) reward[i] -= LosePenalty;
    }
    for(int i=0; i<numAgents; i++){
        if(apple == snakes[i].head){
            reward[i] ++;
        }
    }
    // zero-sum
    int diff = reward[0] - reward[1];
    reward[0] = diff;
    reward[1] = -diff;

    if(endState) return;

    // random transition
    if(actionType == 0) return;
    int ca = rand() % numChanceActions;
    while(!validChanceAction(ca)){
        ca = rand() % numChanceActions;
    }
    chanceAction(ca);
    actionType = 0;
}

void State::chanceAction(int actionIndex){
    assert(validChanceAction(actionIndex));
    apple.x = actionIndex / boardy;
    apple.y = actionIndex % boardy;
    actionType = 0;
}

bool State::validChanceAction(int pos){
    int newApplex = pos / boardy;
    int newAppley = pos % boardy;
    if(getGridValue(Pos(newApplex, newAppley)) != -1) return false;
    return true;
    // bool openInt = false;
    // for(int i=1; i<boardx-1; i++){
    //     for(int j=1; j<boardy-1; j++){
    //         if(getGridValue(Pos(i,j)) == -1){
    //             openInt = true;
    //             break;
    //         }
    //     }
    //     if(openInt) break;
    // }
    // return (!openInt) || (1 <= newApplex && newApplex < boardx-1 
    //                     && 1 <= newAppley && 1 <= newAppley-1);
}

string State::toString() { // optional function for debugging
    string outString = "";
    outString += "Timer: " + to_string(timer) + '\n';
    outString += "Action type: " + to_string(actionType) + '\n';
    outString += "Snake sizes: ";
    for(int i=0; i<numAgents; i++){
        outString += to_string(snakes[i].size) + ' ';
    }
    outString += '\n';
    char output[2*boardx+1][2*boardy+1];
    for(int i=0; i<2*boardx+1; i++){
        for(int j=0; j<2*boardy+1; j++){
            output[i][j] = ' ';
        }
    }
    for(int i=0; i<2*boardx+1; i++){
        output[i][0] = '#';
        output[i][2*boardy] = '#';
    }
    for(int j=0; j<2*boardy+1; j++){
        output[0][j] = '#';
        output[2*boardx][j] = '#';
    }
    char body[numAgents] = {'x', 'y'};
    char head[numAgents] = {'X', 'Y'};
    for(int i=0; i<boardx; i++){
        for(int j=0; j<boardy; j++){
            int val = getGridValue(Pos(i, j));
            int snakeID = val / 5;
            int d = val % 5;
            char out;
            if(apple == Pos(i, j)){
                out = 'A';
            }
            else if(val == -1){
                out = '.';
            }
            else if(d == 4){
                out = head[snakeID];
            }
            else{
                out = body[snakeID];
                char bar;
                if(d%2 == 0) bar = '-';
                else bar = '|';
                output[2*i+1 + dir[d][0]][2*j+1 + dir[d][1]] = bar;
            }
            output[2*i+1][2*j+1] = out;
        }
    }
    for(int i=0; i<2*boardx+1; i++){
        for(int j=0; j<2*boardy+1; j++){
            outString += output[i][j];
        }
        outString += '\n';
    }
    outString += '\n';
    return outString;
}

bool State::equals(const State& s) const{
    if(actionType != s.actionType) return false;
    if(timer != s.timer) return false;
    assert(endState == s.endState);
    for(int i=0; i<numAgents; i++){
        if(snakes[i] != s.snakes[i]) return false;
    }
    if(apple != s.apple) return false;
    for(int i=0; i<boardx; i++){
        for(int j=0; j<boardy; j++){
            if(grid[i][j] != s.grid[i][j]) return false;
        }
    }
    return true;
}

size_t State::hashValue() const{
    long M = 10000000019;
    long val = 0;
    val = (val * 29 + timer) % M;
    val = (val * 29 + actionType) % M;
    assert(actionType == 0);
    val = (val * 29 + apple.x) % M;
    val = (val * 29 + apple.y) % M;
    for(int i=0; i<boardx; i++){
        for(int j=0; j<boardy; j++){
            val = (val * 29 + grid[i][j]) % M;
        }
    }
    return val;
}
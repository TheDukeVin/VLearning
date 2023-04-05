
#include "vlearn.h"

State::State(){
    currPlayer = 0;
    for(int i=0; i<TIME_HORIZON; i++){
        event_seq[i] = -1;
    }
    endState = false;
    for(int i=0; i<NUM_AGENT; i++){
        committed_chips[i] = 1;
        folded[i] = false;
    }
    currTime = 0;
}

int State::topBet(){
    for(int i=currTime-1; i>=0; i--){
        if(event_seq[i] != 0){
            return event_seq[i];
        }
    }
    return 1;
}

bool State::validAction(int action, int playerID){
    if(playerID != currPlayer) return action == 0;
    int top = topBet();
    if(action == FOLD){
        return committed_chips[currPlayer] < top;
    }
    return action == top || action >= top * 2 || action == maxBet;
}

void State::makeAction(double* reward){
    assert(currTime < TIME_HORIZON);
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = 0;
        assert(validAction(actions[i], i));
    }
    int action = actions[currPlayer];
    event_seq[currTime] = action;
    currTime ++;
    if(action == FOLD){
        folded[currPlayer] = true;
        reward[currPlayer] = -committed_chips[currPlayer];
    }
    else{
        committed_chips[currPlayer] = action;
    }
    // check for endState
    // the game ends when all players who have not folded have the same number of committed chips
    // except for in the beginning when everyone commits one chip. in that case, the game
    // ends if all players check.
    bool equalChips = true;
    int numChips = -1;
    for(int i=0; i<NUM_AGENT; i++){
        if(!folded[i]){
            if(numChips == -1){
                numChips = committed_chips[i];
            }
            else if(numChips != committed_chips[i]){
                equalChips = false;
            }
        }
    }
    endState = equalChips && (numChips > 1 || currPlayer == NUM_AGENT - 1);
    if(endState){
        showdown(reward);
        return;
    }
    // Loop around to next player if not end.
    for(int player = currPlayer + 1; player < currPlayer + NUM_AGENT; player++){
        if(!folded[player % NUM_AGENT]){
            currPlayer = player % NUM_AGENT;
            return;
        }
    }
    assert(false);
}

string State::toString(){
    string s = "Events:\n";
    for(int i=0; i<currTime; i++){
        s += to_string(event_seq[i]) + ' ';
        if(i % 3 == 2){
            s += '\n';
        }
    }
    s += '\n';
    return s;
}

void State::showdown(double* reward){
    int maxVal = -1;
    int winner = -1;
    for(int i=0; i<NUM_AGENT; i++){
        if(folded[i]) continue;
        if(maxVal < revealed_types[i].cardVal){
            maxVal = revealed_types[i].cardVal;
            winner = i;
        }
    }
    assert(winner != -1);

    // pot includes all players including those that folded
    int pot = 0;
    for(int i=0; i<NUM_AGENT; i++){
        pot += committed_chips[i];
    }
    for(int i=0; i<NUM_AGENT; i++){
        if(folded[i]) continue;
        reward[i] = -committed_chips[i];
        if(i == winner){
            reward[i] += pot;
        }
    }
}

bool State::equals(const State& s) const {
    for(int i=0; i<TIME_HORIZON; i++){
        if(event_seq[i] != s.event_seq[i]) return false;
    }
    assert(currPlayer == s.currPlayer);
    assert(currTime == s.currTime);
    assert(endState == s.endState);
    for(int i=0; i<NUM_AGENT; i++){
        assert(committed_chips[i] == s.committed_chips[i]);
        assert(folded[i] == s.folded[i]);
    }
    return true;
}

size_t State::hashValue() const{
    long val = 0;
    for(int i=0; i<TIME_HORIZON; i++){
        val = (val * 123 + event_seq[i]) % M;
    }
    return val;
}
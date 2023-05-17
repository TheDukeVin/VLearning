
#include "vlearn.h"

unordered_set<State, StateHash> nextStates(State& s, int recAgent){
    unordered_set<State, StateHash> states;
    if(recAgent == NUM_AGENT){
        double hold[NUM_AGENT];
        State s_new = s;
        // cout<<"Trying actions: ";
        // for(int i=0; i<NUM_AGENT; i++){
        //     cout<<s.actions[i]<<' ';
        // }
        // cout<<'\n';
        s_new.makeAction(hold);
        states.insert(s_new);
        return states;
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!s.validAction(i, recAgent)) continue;
        s.actions[recAgent] = i;
        for(auto t : nextStates(s, recAgent+1)){
            states.insert(t);
        }
    }
    return states;
}

unordered_set<State, StateHash> all_states(){
    unordered_set<State, StateHash> states;
    vector<State> currStates;
    currStates.push_back(State());
    // int counter = 0;
    while(!currStates.empty()){
        // if(counter % 10000 == 0){
        //     cout<<counter<<'\n';
        // }
        // counter++;
        State s = currStates.back();
        // cout<<s.toString();
        states.insert(s);
        currStates.pop_back();
        if(s.endState){
            continue;
        }
        int i = 0;
        for(auto t : nextStates(s, 0)){
            if(states.find(t) == states.end()){
                currStates.push_back(t);
            }
            i ++;
        }
        assert(i < pow(NUM_ACTIONS, NUM_AGENT));
        // int numValidActions = 0;
        // for(int i=0; i<NUM_ACTIONS; i++){
        //     if(s.validAction(i)){
        //         State next_s = s;
        //         next_s.makeAction(i);
        //         currStates.push_back(next_s);
        //         numValidActions++;
        //     }
        // }
        // assert(numValidActions > 1);
    }
    return states;
}

#include "vlearn.h"

VLearn::VLearn(){
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            policy[i][s] = AdvBandit(s, i);
        }
    }
}

void VLearn::rollOut(){
    double reward[NUM_AGENT];
    State traj[TIME_HORIZON+1];
    int t;
    for(t=0; t<TIME_HORIZON; t++){
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]].sampleAction();
        }
        traj[t+1].makeAction(reward);

        for(int i=0; i<NUM_AGENT; i++){
            policy[i][traj[t]].update(traj[t+1].actions[i], policy[i][traj[t+1]].value + reward[i]);
        }
        if(traj[t+1].endState){
            break;
        }
    }
}
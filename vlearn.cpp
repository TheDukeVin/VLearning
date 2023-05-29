
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

void VLearn::printGame(){
    double reward[NUM_AGENT];
    State traj[TIME_HORIZON+1];
    int t;
    cout<<"New Rollout:\n";
    for(t=0; t<TIME_HORIZON; t++){
        cout<<"State: "<<traj[t].toString();
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            cout<<"Agent "<<i<<" policy: ";
            for(auto a : traj[t].validActions(i)){
                cout<<a<<"_"<<policy[i][traj[t]].actionProb[a]<<' ';
            }
            cout<<'\n';
        }
        cout<<"Actions: ";
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]].sampleAction();
            cout<<traj[t+1].actions[i]<<' ';
        }
        cout<<'\n';
        traj[t+1].makeAction(reward);
        cout<<"Rewards: ";
        for(int i=0; i<NUM_AGENT; i++){
            cout<<reward[i]<<' ';
        }
        cout<<'\n';
        if(traj[t+1].endState){
            break;
        }
    }
    cout<<"\n\n";
}
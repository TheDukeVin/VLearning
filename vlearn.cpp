
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
                // cout<<a;
                cout<<actionNames[a]; // OPTIONAL: print action name
                cout<<"_"<<policy[i][traj[t]].actionProb[a]<<' ';
            }
            cout<<'\n';
        }
        cout<<"Actions: ";
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]].sampleAction();
            // cout<<traj[t+1].actions[i]<<' ';
            cout<<actionNames[traj[t+1].actions[i]]<<' '; // OPTIONAL: print action name
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

void VLearn::save(string outFile){
    ofstream fout(outFile);
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            for(int j=0; j<NUM_ACTIONS; j++){
                fout << policy[i][s].aggPolicy[j] << ' ';
            }
        }
    }
}

void VLearn::load(string inFile){
    ifstream fin(inFile);
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            // Adjust for read/write precision loss
            double sum = 0;
            for(int j=0; j<NUM_ACTIONS; j++){
                fin >> policy[i][s].actionProb[j];
                if(policy[i][s].actionProb[j] >= 0){
                    sum += policy[i][s].actionProb[j];
                }
            }

            assert(abs(sum - 1) < 1e-03);
            for(int j=0; j<NUM_ACTIONS; j++){
                if(policy[i][s].actionProb[j] >= 0){
                    policy[i][s].actionProb[j] /= sum;
                }
            }
        }
    }
}
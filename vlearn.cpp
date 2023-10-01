
#include "vlearn.h"

// VLearn::VLearn(){
//     for(int i=0; i<NUM_AGENT; i++){
//         for(auto s : all_states()){
//             if(s.endState) continue;
//             policy[i][s] = AdvBandit(s, i);
//         }
//     }
// }

void VLearn::rollOut(){
    double reward[TIME_HORIZON+1][NUM_AGENT];
    State traj[TIME_HORIZON+1];
    int t;
    for(t=0; t<=TIME_HORIZON; t++){
        if(policy[0].find(traj[t]) == policy[0].end()){
            for(int i=0; i<NUM_AGENT; i++){
                policy[i][traj[t]] = AdvBandit(traj[t], i);
            }
        }
        if(traj[t].endState){
            break;
        }
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]].sampleAction();
        }
        traj[t+1].makeAction(reward[t]);

        // for(int i=0; i<NUM_AGENT; i++){
        //     policy[i][traj[t]].update(traj[t+1].actions[i], policy[i][traj[t+1]].value + reward[i]);
        // }
    }
    assert(t <= TIME_HORIZON);
    assert(traj[t].endState);
    double value[NUM_AGENT];
    for(int i=0; i<NUM_AGENT; i++){
        value[i] = traj[t].endValue(i);
    }
    for(; t>0; t--){
        for(int i=0; i<NUM_AGENT; i++){
            if(VALUE_FLAG == END){
                value[i] += reward[t-1][i];
                policy[i][traj[t-1]].update(traj[t].actions[i], value[i]);
            }
            else{
                assert(VALUE_FLAG == REC);
                policy[i][traj[t-1]].update(traj[t].actions[i], policy[i][traj[t]].value + reward[t-1][i]);
            }
        }
    }
}

void VLearn::printGame(){
    double reward[NUM_AGENT];
    State traj[TIME_HORIZON+1];
    int t;
    cout<<"New Rollout:\n";
    for(t=0; t<TIME_HORIZON; t++){
        if(policy[0].find(traj[t]) == policy[0].end()){
            for(int i=0; i<NUM_AGENT; i++){
                policy[i][traj[t]] = AdvBandit(traj[t], i);
            }
        }
        if(traj[t].endState){
            break;
        }
        cout<<"State: "<<traj[t].toString()<<'\n';
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            cout<<"Agent "<<i<<" value: " << policy[i][traj[t]].value <<", policy: ";
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
    }
    cout<<"End State: "<<traj[t].toString()<<'\n';
    cout<<"End Value: ";
    for(int i=0; i<NUM_AGENT; i++){
        cout<<policy[i][traj[t]].value<<' ';
    }
    cout<<"\n\n";
}

void VLearn::save(string outFile){
    ofstream fout(outFile);
    for(auto & [s, hold] : policy[0]){
        fout << s.toString() << '\n';
        for(int i=0; i<NUM_AGENT; i++){
            fout << policy[i][s].value << ' ';
            for(int j=0; j<NUM_ACTIONS; j++){
                fout << policy[i][s].aggPolicy[j] << ' ';
            }
            fout << '\n';
        }
    }
}

void VLearn::load(string inFile){
    ifstream fin(inFile);
    string line;
    while(getline(fin, line)){
        State s(line);
        for(int i=0; i<NUM_AGENT; i++){
            policy[i][s] = AdvBandit(s, i);
            // Adjust for read/write precision loss
            double sum = 0;
            getline(fin, line);
            istringstream iss(line);
            iss >> policy[i][s].value;
            for(int j=0; j<NUM_ACTIONS; j++){
                iss >> policy[i][s].actionProb[j];
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
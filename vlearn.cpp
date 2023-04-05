
#include "vlearn.h"

VLearn::VLearn(){
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            for(auto t : all_types()){
                policy[i][s][t] = AdvBandit(s, i);
            }
        }
    }
}

void VLearn::rollOut(){
    // cout<<"NEW ROLLOUT\n";
    Type types[NUM_AGENT];
    double reward[NUM_AGENT];
    init_type(types);

    // for(int i=0; i<NUM_AGENT; i++){
    //     cout<<"Agent "<<i<<" type: "<<types[i].toString()<<'\n';
    // }

    State traj[TIME_HORIZON+1];
    int t;
    for(t=0; t<TIME_HORIZON; t++){
        // cout<<"Time step "<<t<<'\n';
        // cout<<traj[t].toString()<<'\n';
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]][types[i]].sampleAction();
            traj[t+1].revealed_types[i] = types[i];
            // cout<<"Agent "<<i<<" chose action "<<traj[t+1].actions[i]<<'\n';
        }
        traj[t+1].makeAction(reward);

        for(int i=0; i<NUM_AGENT; i++){
            // cout<<"Agent "<<i<<" recieved reward "<<reward[i]<<". Total return is "<<policy[i][traj[t+1]][types[i]].value + reward[i]<<'\n';
            policy[i][traj[t]][types[i]].update(traj[t+1].actions[i], policy[i][traj[t+1]][types[i]].value + reward[i]);
        }
        if(traj[t+1].endState){
            break;
        }
    }
}

void VLearn::train(int numIter){
    for(int i=0; i<numIter; i++){
        rollOut();
    }
}

void VLearn::printGame(){
    Type types[NUM_AGENT];
    double reward[NUM_AGENT];
    init_type(types);

    for(int i=0; i<NUM_AGENT; i++){
        cout<<"Agent "<<i<<" type: "<<types[i].toString()<<'\n';
    }

    State traj[TIME_HORIZON+1];
    int t;
    cout<<"Starting game:\n";
    for(t=0; t<TIME_HORIZON; t++){
        cout<<"Time step "<<t<<'\n';
        cout<<traj[t].toString()<<'\n';
        traj[t+1] = traj[t];
        for(int i=0; i<NUM_AGENT; i++){
            traj[t+1].actions[i] = policy[i][traj[t]][types[i]].sampleAction();
            cout<<"Agent "<<i<<" policy:\n";
            for(int j=0; j<NUM_ACTIONS; j++){
                cout<<policy[i][traj[t]][types[i]].actionProb[j]<<' ';
            }
            cout<<'\n';
            traj[t+1].revealed_types[i] = types[i];
            cout<<"Agent "<<i<<" chose action "<<traj[t+1].actions[i]<<'\n';
        }
        traj[t+1].makeAction(reward);

        // for(int i=0; i<NUM_AGENT; i++){
        //     cout<<"Agent "<<i<<" recieved reward "<<reward[i]<<'\n';
        // }
        if(traj[t+1].endState){
            break;
        }
    }
}

void VLearn::save(string outFile){
    ofstream fout(outFile);
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            for(auto t : all_types()){
                for(int j=0; j<NUM_ACTIONS; j++){
                    fout << policy[i][s][t].actionProb[j] << ' ';
                }
            }
        }
    }
}

void VLearn::load(string inFile){
    ifstream fin(inFile);
    for(int i=0; i<NUM_AGENT; i++){
        for(auto s : all_states()){
            if(s.endState) continue;
            for(auto t : all_types()){
                // Adjust for read/write precision loss
                double sum = 0;
                for(int j=0; j<NUM_ACTIONS; j++){
                    fin >> policy[i][s][t].actionProb[j];
                    if(policy[i][s][t].actionProb[j] >= 0){
                        sum += policy[i][s][t].actionProb[j];
                    }
                }
                for(int j=0; j<NUM_ACTIONS; j++){
                    policy[i][s][t].actionProb[j] /= sum;
                }
            }
        }
    }
}
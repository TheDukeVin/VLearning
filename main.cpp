
#include "vlearn.h"

VLearn VL;

double getExploitability(int agentID);

void train(){
    int start_time = time(0);
    // unordered_set<State, StateHash> states = all_states();
    ofstream expOut("exploit.out");
    ofstream polOut("conv.out");
    {
        ofstream fout("log.out");
        // fout<<"Game size: "<<states.size()<<'\n';
        fout<<"Simulating games: \n";
    }

    for(int i=0; i<NUM_ROLLOUTS; i++){
        if(i % 1000000 == 0){
            ofstream fout("log.out", ios::app);
            fout<<"Iteration "<< i << " Time " << (time(0) - start_time) << '\n';
        }
        VL.rollOut();
        if(i % 1000000 == 0){
            for(int j=0; j<NUM_AGENT; j++){
                expOut<<getExploitability(j)<<',';
            }
            expOut<<'\n';
        }
    }
    VL.save("policy.out");

    {
        ofstream fout("log.out", ios::app);
        fout<<"Run time: "<<(time(0) - start_time)<<'\n';
    }
}

void printGames(){
    VL.load("policy.out");
    for(int i=0; i<10; i++){
        VL.printGame();
    }
}

unordered_map<State, double, StateHash> valueStore;

double getValue(int agentID, State s, bool maxFlag);

double Q(int agentID, int action, State s, bool maxFlag){
    int index = 0;
    for(; index<NUM_AGENT; index++){
        if(s.actions[index] == -1 && index != agentID){
            break;
        }
    }
    if(index == NUM_AGENT){
        s.actions[agentID] = action;
        double sum = 0;
        for(auto poss : s.transitionDistribution(agentID)){
            sum += (getValue(agentID, poss.first, maxFlag) + poss.second.second) * poss.second.first;
        }
        return sum;
    }
    double sum = 0;
    for(auto a : s.validActions(index)){
        s.actions[index] = a;
        sum += VL.policy[index][s].aggPolicy[a] * Q(agentID, action, s, maxFlag);
    }
    return sum;
}

double getValue(int agentID, State s, bool maxFlag){
    // cout<<"Get Value "<<agentID<<' '<<s.toString()<<' '<<maxFlag<<'\n';
    if(VL.policy[0].find(s) == VL.policy[0].end()){
        for(int i=0; i<NUM_AGENT; i++){
            VL.policy[i][s] = AdvBandit(s, i);
        }
    }
    if(valueStore.find(s) != valueStore.end()) return valueStore[s];
    if(s.endState) return VL.policy[agentID][s].value;
    double Q_values[NUM_ACTIONS];
    for(auto a : s.validActions(agentID)){
        for(int i=0; i<NUM_AGENT; i++){
            s.actions[i] = -1;
        }
        Q_values[a] = Q(agentID, a, s, maxFlag);
    }
    double ans;
    if(maxFlag){
        double maxQ = 0;
        for(auto a : s.validActions(agentID)){
            maxQ = max(maxQ, Q_values[a]);
            // cout<<"Q value: "<<Q_values[a]<<'\n';
        }
        ans = maxQ;
    }
    else{
        double sum = 0;
        for(auto a : s.validActions(agentID)){
            sum += VL.policy[agentID][s].aggPolicy[a] * Q_values[a];
        }
        ans = sum;
    }
    valueStore[s] = ans;
    return ans;
}

double getExploitability(int agentID = -1){
    State s;
    if(agentID >= 0){
        double BRValue = 0;
        valueStore = unordered_map<State, double, StateHash>();
        for(auto poss : s.initialDistribution()){
            BRValue += getValue(agentID, poss.first, true) * poss.second;
        }
        double currValue = 0;
        valueStore = unordered_map<State, double, StateHash>();
        for(auto poss : s.initialDistribution()){
            currValue += getValue(agentID, poss.first, false) * poss.second;
        }
        return BRValue - currValue;
    }
    double sum = 0;
    for(int i=0; i<NUM_AGENT; i++){
        sum += getExploitability(i);
    }
    return sum;
}

// double getReward(int agentID, int action0, int action1){
//     if(agentID == 0) return matrix0[action0][action1];
//     return matrix1[action0][action1];
// }

// double testExploitability(int agentID){
//     double value = 0;
//     for(int i=0; i<NUM_ACTIONS; i++){
//         for(int j=0; j<NUM_ACTIONS; j++){
//             value += VL.policy[0][State()].aggPolicy[i] * VL.policy[1][State()].aggPolicy[j] * getReward(agentID, i, j);
//         }
//     }
//     // cout<<"Value: "<<value<<'\n';
//     double maxValue = -1000;
//     for(int i=0; i<NUM_ACTIONS; i++){
//         double candValue = 0;
//         for(int j=0; j<NUM_ACTIONS; j++){
//             int actions[2];
//             actions[agentID] = i;
//             actions[1-agentID] = j;
//             candValue += VL.policy[1-agentID][State()].aggPolicy[j] * getReward(agentID, actions[0], actions[1]);
//         }
//         if(maxValue < candValue){
//             maxValue = candValue;
//         }
//         // cout<<"Utility of action "<<i<<": "<<candValue<<'\n';
//     }
//     // cout<<"Difference from optimal response: "<<(maxValue - value)<<'\n';
//     return maxValue - value;
// }

int main(){
    srand(time(NULL));
    // train();
    // cout<<getExploitability()<<'\n';
    printGames();
}

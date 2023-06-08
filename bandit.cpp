
#include "vlearn.h"

AdvBandit::AdvBandit(){
    value = 0; // End state should still have value 0 for base case
    for(int i=0; i<NUM_ACTIONS; i++){
        aggPolicy[i] = actionProb[i] = -1;
    }
}

AdvBandit::AdvBandit(State s_, int ag){
    // value = 0;
    // OPTIONAL: rescale initialized rewards to match 0 reward in the reward space
    value = (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - s_.time);
    for(int i=0; i<NUM_ACTIONS; i++){
        aggPolicy[i] = actionProb[i] = -1;
    }
    s = s_;
    agentID = ag;
    validActions = s.validActions(ag);
    for(auto a : validActions){
        sumLoss[a] = 0;
        aggPolicy[a] = actionProb[a] = 1.0 / validActions.size();
    }
    visitCount = 0;
}

void AdvBandit::update(int action, double newValue){
    // Update value
    double lr = learnRate();
    double er = explorationRate();
    visitCount ++;
    value = (1 - lr) * value + lr * (newValue + er);
    if(validActions.size() == 1) return;

    // Update policy
    double loss = 1 - newValue / TIME_HORIZON;
    sumLoss[action] += loss / (actionProb[action]);

    double minLoss = 1e+10;
    for(auto a : validActions){
        if(sumLoss[a] < minLoss) minLoss = sumLoss[a];
    }
    double sum = 0;
    for(auto a : validActions){
        actionProb[a] = exp(-lr * (sumLoss[a] - minLoss));
        sum += actionProb[a];
    }
    for(auto a : validActions){
        actionProb[a] /= sum;
        assert(!::isnan(actionProb[a]));
        aggPolicy[a] = (aggPolicy[a] * (visitCount-1) + actionProb[a]) / visitCount;
    }
}

int AdvBandit::sampleAction(){
    if(validActions.size() == 1) return validActions[0];
    return sampleDist(actionProb, NUM_ACTIONS);
}
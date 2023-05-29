
#include "vlearn.h"

AdvBandit::AdvBandit(){
    value = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        actionProb[i] = -1;
    }
}

AdvBandit::AdvBandit(State s_, int ag){
    value = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        actionProb[i] = -1;
    }
    s = s_;
    agentID = ag;
    validActions = s.validActions(ag);
    for(auto a : validActions){
        sumLoss[a] = 0;
        actionProb[a] = 1.0 / validActions.size();
        aggPolicy[a] = 0;
    }
    visitCount = 0;
}

void AdvBandit::update(int action, double newValue){
    // cout<<newValue<<' ';
    // Update value
    double lr = learnRate();
    double er = explorationRate();
    // double skew = sampleSkew();
    // double currWeight = lossWeight();
    // if(visitCount > 1) prod_learn *= 1 - lr;
    visitCount ++;
    value = (1 - lr) * value + lr * (newValue + er);
    if(validActions.size() == 1) return;
    // Update policy
    double loss = 1-newValue / TIME_HORIZON;
    sumLoss[action] += loss / (actionProb[action]);

    double minLoss = 1e+10;
    for(auto a : validActions){
        if(sumLoss[a] < minLoss) minLoss = sumLoss[a];
    }
    double sum = 0;
    for(auto a : validActions){
        actionProb[a] = exp(-lr * (sumLoss[a] - minLoss));
        // cout<<sumLoss[i]<<' ';
        sum += actionProb[a];
    }
    // cout<<'\n';
    for(auto a : validActions){
        actionProb[a] /= sum;
        assert(!isnan(actionProb[a]));
        aggPolicy[a] = (aggPolicy[a] * (visitCount-1) + actionProb[a]) / visitCount;
    }
}

int AdvBandit::sampleAction(){
    if(validActions.size() == 1) return validActions[0];
    return sampleDist(actionProb, NUM_ACTIONS);
}

#include "vlearn.h"

AdvBandit::AdvBandit(){
    value = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        actionProb[i] = -1;
    }
}

AdvBandit::AdvBandit(State s_, int ag){
    s = s_;
    agentID = ag;
    numValidAction = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        validAction[i] = s.validAction(i, ag);
        if(validAction[i]) numValidAction ++;
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        if(validAction[i]){
            sumLoss[i] = 0;
            actionProb[i] = 1.0 / numValidAction;
            aggPolicy[i] = 0;
            soleAction = i;
        }
        else{
            actionProb[i] = -1;
        }
    }
    assert(numValidAction > 0);
    visitCount = 0;
    value = 0;
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
    if(numValidAction == 1) return;
    // Update policy
    double loss = 1-newValue / TIME_HORIZON;
    sumLoss[action] += loss / (actionProb[action]);

    double minLoss = 1e+10;
    for(int i=0; i<NUM_ACTIONS; i++){
        if(validAction[i] && sumLoss[i] < minLoss) minLoss = sumLoss[i];
    }
    double sum = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!validAction[i]) continue;
        actionProb[i] = exp(-lr * (sumLoss[i] - minLoss));
        // cout<<sumLoss[i]<<' ';
        sum += actionProb[i];
    }
    // cout<<'\n';
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!validAction[i]) continue;
        actionProb[i] /= sum;
        assert(!isnan(actionProb[i]));
        aggPolicy[i] = (aggPolicy[i] * (visitCount-1) + actionProb[i]) / visitCount;
    }
}

int AdvBandit::sampleAction(){
    if(numValidAction == 1) return soleAction;
    return sampleDist(actionProb, NUM_ACTIONS);
}
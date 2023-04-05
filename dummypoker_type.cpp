
#include "vlearn.h"

Type::Type(int val){
    cardVal = val;
}

string Type::toString(){
    return to_string(cardVal);
}

size_t Type::hashValue() const{
    return cardVal;
}

bool Type::equals(const Type& t) const {
    return cardVal == t.cardVal;
}

unordered_set<Type, TypeHash> all_types(){
    unordered_set<Type, TypeHash> types;
    for(int i=0; i<deckSize; i++){
        types.insert(Type(i));
    }
    return types;
}

void init_type(Type* types){
    bool used[deckSize];
    for(int i=0; i<deckSize; i++){
        used[i] = false;
    }
    for(int i=0; i<NUM_AGENT; i++){
        while(true){
            types[i] = Type(rand() % deckSize);
            if(!used[types[i].cardVal]){
                used[types[i].cardVal] = true;
                break;
            }
        }
    }
}
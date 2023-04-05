
#include "vlearn.h"

string Type::toString() const {
    return "0";
}

size_t Type::hashValue() const {
    return 0;
}

bool Type::equals(const Type& t) const {
    return true;
}

unordered_set<Type, TypeHash> all_types(){
    unordered_set<Type, TypeHash> types;
    types.insert(Type());
    return types; 
}

void init_type(Type* types){
    for(int i=0; i<NUM_AGENT; i++){
        types[i] = Type();
    }
}
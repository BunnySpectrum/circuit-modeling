#include "node.h"

Node::Node(){
    uid = UID::next_id();
    name = "";
};

std::ostream &operator<<(std::ostream &os, Node const &node){
    return os << node.name << ":" << node.uid;
}

bool Node::operator==(const Node &otherNode) const{
    if(this->uid == otherNode.uid){
        return true;
    }else{
        return false;
    }
}

size_t Node::HashFunction::operator()(const Node &node) const{
    // return 0;
    size_t hash = std::hash<int64_t>()(node.uid);
    return hash;
}

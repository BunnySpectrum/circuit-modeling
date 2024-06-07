#include "node.h"

Node::Node(std::string objName, std::string keyValue){
    uid = UID::next_id();
    name = objName;
    key = keyValue;
}


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



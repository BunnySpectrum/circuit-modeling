#include "node.h"

Node::Node(std::string objName){
    uid = UID::next_id();
    name = objName;
};

bool Node::connect(std::shared_ptr<Node> pNode){
    this->connections.insert(pNode);
    pNode->connections.insert(shared_from_this());

    return true;
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



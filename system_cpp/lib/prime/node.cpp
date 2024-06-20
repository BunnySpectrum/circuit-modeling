#include "node.h"

Node::Node(Key _, std::string objName, std::string keyValue){
    uid = UID::next_id();
    name = objName;
    key = keyValue;
}

std::unique_ptr<netlist::Node> Node::to_proto(){
    auto pNodePB = std::make_unique<netlist::Node>();
    pNodePB->set_uid(uid);
    pNodePB->set_name(name);
    pNodePB->set_key(key);

    return std::move(pNodePB);
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



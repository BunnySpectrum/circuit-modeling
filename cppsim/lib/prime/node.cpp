#include "node.h"

Node::Node(std::string objName, std::string keyValue){
    uid = UID::next_id();
    name = objName;
    key = keyValue;
}

std::unique_ptr<netlist::Node> Node::to_proto(){
    auto puNodePB = std::make_unique<netlist::Node>();
    puNodePB->set_uid(uid);
    puNodePB->set_name(name);
    puNodePB->set_key(key);

    return std::move(puNodePB);
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



#include "net.h"

Net::Net(std::string objName){
    uid = UID::next_id();
    name = objName;
};

bool Net::add_node(std::shared_ptr<Node> pNode){
    this->connections.insert(pNode);
    // pNode->net = shared_from_this();

    return true;
}



std::ostream &operator<<(std::ostream &os, Net const &net){
    return os << "Net: " << net.name << ":" << net.uid;
}

bool Net::operator==(const Net &otherNet) const{
    if(this->uid == otherNet.uid){
        return true;
    }else{
        return false;
    }
}



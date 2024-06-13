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

std::unique_ptr<netlist::Net> Net::to_proto(){
    auto pNetPB = std::make_unique<netlist::Net>();
    pNetPB->set_uid(uid);
    pNetPB->set_name(name);

    google::protobuf::RepeatedPtrField<netlist::Net::Connection> *pNetConnsPB = pNetPB->mutable_connections();
    
    for(const std::shared_ptr<Node>& pNode : this->connections){
        auto pNetConnPB = std::make_unique<netlist::Net::Connection>();

        pNetConnPB->set_node_uid(pNode->uid);
        pNetConnPB->set_node_name(pNode->name);
        pNetConnsPB->AddAllocated(pNetConnPB.release());
    }

    return std::move(pNetPB);
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



#include "voltage_source.h"

Voltage_Source::Voltage_Source(std::string objName):
    pPosNode(std::make_shared<Node>(objName + "-P", "P")),
    pNegNode(std::make_shared<Node>(objName + "-N", "N")){
    uid_ = UID::next_id();
    name_ = objName;
}

std::list<std::shared_ptr<Node>> Voltage_Source::get_nodes(){
    std::list<std::shared_ptr<Node>> result;
    result.push_back(pPosNode);
    result.push_back(pNegNode);
    return result;
}

std::unique_ptr<netlist::Element> Voltage_Source::to_proto(){
    auto pElementPB = std::make_unique<netlist::Element>();

    pElementPB->set_uid(uid_);
    pElementPB->set_name(name_);
    pElementPB->set_type(netlist::ElementType::ELEMENT_TYPE_VS);

    google::protobuf::RepeatedPtrField<netlist::Node> *pElementNodesPB = pElementPB->mutable_nodes();

    auto pNodePB = pPosNode->to_proto();
    pElementNodesPB->AddAllocated(pNodePB.release());
    
    pNodePB = pNegNode->to_proto();
    pElementNodesPB->AddAllocated(pNodePB.release());

    return std::move(pElementPB);
}
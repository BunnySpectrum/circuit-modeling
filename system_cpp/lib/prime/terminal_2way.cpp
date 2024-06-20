#include "terminal_2way.h"

Terminal_2Way::Terminal_2Way(std::string objName):
    pT1Node(Node::create(objName + "-T1", "T1")),
    pT2Node(Node::create(objName + "-T2", "T2")){
    uid_ = UID::next_id();
    name_ = objName;
}

std::list<std::shared_ptr<Node>> Terminal_2Way::get_nodes(){
    std::list<std::shared_ptr<Node>> result;
    result.push_back(pT1Node);
    result.push_back(pT2Node);
    return result;
}

std::unique_ptr<netlist::Element> Terminal_2Way::to_proto(){
    auto pElementPB = std::make_unique<netlist::Element>();

    pElementPB->set_uid(uid_);
    pElementPB->set_name(name_);
    pElementPB->set_type(netlist::ElementType::ELEMENT_TYPE_PASSIVE_2T);

    google::protobuf::RepeatedPtrField<netlist::Node> *pElementNodesPB = pElementPB->mutable_nodes();

    auto pNodePB = pT1Node->to_proto();
    pElementNodesPB->AddAllocated(pNodePB.release());
    
    pNodePB = pT2Node->to_proto();
    pElementNodesPB->AddAllocated(pNodePB.release());

    return std::move(pElementPB);
}

#ifndef _NET_H_
#define _NET_H_

#include <unordered_set>
#include <iostream>

#include "prime/node.h"
#include "utils/uid.h"

// class Node;

class Net : public std::enable_shared_from_this<Net> { 
    public:
        bool operator==(const Net &otherNet) const;
       
        Net(std::string objName);
        bool add_node(std::shared_ptr<Node> pNode);
        size_t uid;
        std::string name;
        std::unordered_set<std::shared_ptr<Node>> connections;
        friend std::ostream &operator<<(std::ostream &os, Net const &net);        

};

template<>
struct std::hash<Net>
{
    size_t operator()(const Net &net) const{
        size_t hash = std::hash<int64_t>()(net.uid);
        return hash;
    }
};


#endif
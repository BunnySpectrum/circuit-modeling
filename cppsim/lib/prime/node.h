#ifndef _NODE_H_
#define _NODE_H_

#include <unordered_set>
#include <iostream>

#include "utils/uid.h"

class Node : public std::enable_shared_from_this<Node> { 
    public:
        bool operator==(const Node &otherNode) const;
       
        Node(std::string objName, std::string key); // Primary constructor
        Node(std::string objName): Node(objName, ""){} // Delegating constructor

        size_t uid;
        std::string name;
        std::string key;
        friend std::ostream &operator<<(std::ostream &os, Node const &node);        

};

template<>
struct std::hash<Node>
{
    size_t operator()(const Node &node) const{
        size_t hash = std::hash<int64_t>()(node.uid);
        return hash;
    }
};


#endif
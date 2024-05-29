#ifndef _NODE_H_
#define _NODE_H_

#include <unordered_set>
#include <iostream>

#include "utils/uid.h"

class Node{
    public:
        bool operator==(const Node &otherNode) const;
        struct HashFunction{
            size_t operator()(const Node &node) const;
        };

        Node(std::string objName);
        bool connect(Node otherNode);
        size_t uid;
        std::string name;
        std::unordered_set<Node, HashFunction> connections;
        friend std::ostream &operator<<(std::ostream &os, Node const &node);

};



#endif
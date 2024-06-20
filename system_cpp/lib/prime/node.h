#ifndef _NODE_H_
#define _NODE_H_

#include <unordered_set>
#include <iostream>

#include "utils/uid.h"
#include "netlist.pb.h"

class Net;

class Node : public std::enable_shared_from_this<Node> { 
    private:
        struct Key{
            friend Node;
        };

    public:
        bool operator==(const Node &otherNode) const;
       
        Node(Key _, std::string objName, std::string key); // Primary constructor
        Node(Key _, std::string objName): Node(_, objName, ""){} // Delegating constructor

        template<typename... A>
        static std::shared_ptr<Node> create(A&&... params)
        {
            return std::make_shared<Node>(Key(), std::forward<A>(params)...);
        }

        std::unique_ptr<netlist::Node> to_proto();

        int32_t uid;
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
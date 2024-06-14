#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <list>
#include "prime/node.h"

class Element{
    public:
        virtual std::list<std::shared_ptr<Node>> get_nodes() = 0;
        virtual std::unique_ptr<netlist::Element> to_proto() = 0;
        std::string name(){
            return name_;
        }
        int32_t uid(){
            return uid_;
        }

    private:
        ;

    protected:
        int32_t uid_;
        std::string name_;
};


#endif
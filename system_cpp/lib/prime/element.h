#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <list>
#include "prime/node.h"

class Element{
    public:
        virtual std::list<std::shared_ptr<Node>> get_nodes() = 0;
        // virtual ~Element(){};
    private:
        ;
};


#endif

#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include "DfsBase.h"
#include "NodeBase.h"



namespace codewang {

using std::string;

class Node : public DfsBase<Node> , NodeBase{
private:
  string name;   /* ½ÚµãÃû */

public:
  Node():name("null"){};
  Node(const string name){
    this->name = name;
  };

  const string& getName(void);
  const string& toString(void);

};


const string& Node::getName(void) {
    return this->name;
}

const string& Node::toString(void) {
    return this->getName();
}

}

#endif /* _NODE_H_ */


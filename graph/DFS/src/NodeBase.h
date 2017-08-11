#ifndef _NODE_BASE_H_
#define _NODE_BASE_H_

#include <string>

using namespace std;

namespace codewang{

/* 定义节点接口，结点应该实现此接口 */
class NodeBase {
public :
    /* 必须有一个显示自己信息的方法 */
  virtual  const string& toString(void) = 0;
};

}

#endif // _NODE_BASE_H_


#ifndef _NODE_BASE_H_
#define _NODE_BASE_H_

#include <string>

using namespace std;

namespace codewang{

/* ����ڵ�ӿڣ����Ӧ��ʵ�ִ˽ӿ� */
class NodeBase {
public :
    /* ������һ����ʾ�Լ���Ϣ�ķ��� */
  virtual  const string& toString(void) = 0;
};

}

#endif // _NODE_BASE_H_


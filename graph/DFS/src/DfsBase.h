
#ifndef _DFS_BASE_H_
#define _DFS_BASE_H_

#include <iostream>


namespace codewang{

using std::cout;

template <class T>
class DfsBase {
private:
  int color;  /* 节点的颜色 */
  int discover;      /* 被发现时的时间戳 */
  int finish;      /* 搜索完毕之后的时间戳 */
  T*  parent; /* 前驱 */
public:
  static constexpr int WHITE = 0;
  static constexpr int GRAY  = 1;
  static constexpr int BLACK = 2;

  DfsBase():color(WHITE),discover(0),finish(0),parent(NULL) {}

  void setColor(int);
  int  getColor(void);
  void setDiscoverTime(int);
  int  getDiscoverTime(void);
  void setFinishTime(int);
  int  getFinishTime(void);
  void setParent(T&);
  T&   getParent(void);
};

template <class T>
void DfsBase<T>::setColor(int color) {
    if((color > 2) || (color < 0)) {
        cout<<"your color-value "<<color<<" is error.";
        return ;
    }
    this->color = color;
}

template <class T>
int DfsBase<T>::getColor(void) {
    return this->color;
}

template <class T>
void DfsBase<T>::setDiscoverTime(int d) {
    this->discover = d;
}

template <class T>
int DfsBase<T>::getDiscoverTime(void) {
    return this->discover;
}

template <class T>
void DfsBase<T>::setFinishTime(int f) {
    this->finish = f;
}

template<class T>
int DfsBase<T>::getFinishTime(void) {
    return this->finish;
}

template<class T>
void DfsBase<T>::setParent(T& p) {
    this->parent = &p;
}

template<class T>
T& DfsBase<T>::getParent(void) {
    return *(this->parent);
}




}

#endif  /* _DFS_BASE_H_ */


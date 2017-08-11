
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <stdlib.h>

using namespace std;

namespace codewang{

template <class NodeType>
class Graph
{
private:

    /* cpp 容器中存的是元素的副本 */
    vector<NodeType*> nodes;        /* 所有节点 */
    vector<list<NodeType*> > edges; /* 邻接表 */
    int** weight;                  /* 权重 */

    int nCnt;
    int eCnt;

    template<typename T>
    T& __getValueFromIntArray2D(T **arr,int v,int row,int low);  /* 辅助函数，从int**中获取值 */
public:
    Graph() {}
    Graph(NodeType*,int, int**);  /* edges 中可以是权重 */
    ~Graph(){
        if( NULL != this->weight ) {
            for(int i = 0; i < nCnt; ++i) {
                if( *(this->weight + i) != NULL ) {
                    delete this->weight[i];
                }
            }
            delete this->weight;
        }
    }

    NodeType& getNode(int index) {
        return *(this->nodes)[index];
    }

    NodeType& getNode(string name) {
        for(NodeType* n : (this->nodes) ) {
            if( name == n->getName() ) {
                return *n;
            }
        }
    }

    vector<NodeType*>& getNodes(void) {
        return this->nodes;
    }

    list<NodeType*>& getAdj(NodeType& node) {
        for(list<NodeType*>& l : (this->edges)) {
            if( (l.front()->getName()) == node.getName() ){  /* 地址相同，认为是同一个结点 */
                return l;
            }
        }
        cout<<"node "<<node.getName()<<" has none child-node."<<endl;
        return *(new list<NodeType*>());
    }

    void showNodes(void);
    void showEdges(void);
    void showWeights(void);
    void show(void) {
        showNodes();
        showEdges();
        showWeights();
    }
};

/* 辅助函数，从int**中获取值
 *  arr 二维数组指针
 *  v   维度
 *  row,low 要获取值的元素
 */
template<class NodeType>
template<typename T> T& Graph<NodeType>::__getValueFromIntArray2D(T **arr,int v,int row,int low)
{
    if(row >= v) {
        cout<<"your row-number : "
            <<row
            <<" is too big ,it shouldn't bigger than v :"
            <<v
            <<"."
            <<endl;
            return *(new int);
    }
    return (*((T*)(arr) + row*v + low));
}


template<class NodeType>
Graph<NodeType>::Graph(NodeType* nodes,int nCnt, int** edges)
{
    this->eCnt = 0;
    this->nCnt = nCnt;
    /* 拷贝结点到图中 */
    vector<NodeType*>& n = this->nodes;
    vector<list<NodeType*> >& e = this->edges;

    for( int index=0; index<nCnt ;++index ){
        n.push_back(&nodes[index]);
    }

    /* 权重 */
     this->weight = edges;

    if( this->weight == NULL ) {
        cout<<"out of space !"<<endl
            <<"can't alloc space for [weight["<<nCnt<<"]["<<nCnt<<"]]";
        return ;
    }

    /* 解析边信息，到邻接链表 */
    for(int row = 0; row < nCnt; row++) {
        list<NodeType*> l;
        l.push_back(n[row]);
        for(int low = 0; low < nCnt; low++) {    /* 面向有向图 */
            /* 假设不存在负权重
                -1 表示不能到达
                 0 表示自身
            */
            if( __getValueFromIntArray2D(edges,nCnt,row,low) > 0 ) {
                l.push_back(n[low]);
                this->eCnt ++;
            }
        }
        /* 放入邻接表 */
        e.push_back(l);
    }
}






template<class NodeType>
void Graph<NodeType>::showNodes(void)
{
    cout<<"there are "
        <<(this->nodes).size()
        <<" nodes in this graph. they are: "<<endl;

    auto s = (this->nodes).begin(),
         f = (this->nodes).end();

    for(;;) {
         cout<<(*s)->toString()
             <<"-("
             <<(*s)->getDiscoverTime()
             <<"\\"
             <<(*s)->getFinishTime()
             <<")";

         ++s;
         if(s != f) {
            cout<<",";
         }else{
            cout<<endl;
            break;
         }
    }
}

template <class NodeType>
void Graph<NodeType>::showEdges(void)
{
    cout<<"there are "<<this->eCnt<<" edges of this graph:"<<endl;
    auto ptr      = (this->edges).begin(),
         finish   = (this->edges).end();

    for(;ptr != finish; ++ptr) {
        list<NodeType>& l = *ptr;
        auto list_begin = l.begin(),
             list_end   = l.end();
        for(;;) {
            cout<<(*list_begin)->toString();
            list_begin++;
            if( list_begin != list_end ) {
                cout<<"->";
            }else{
                cout<<endl;
                break;
            }
        }
    }
}

template<class NodeType>
void Graph<NodeType>::showWeights(void)
{
    cout<<"this is weight-map of this graph :"<<endl;

    for(int i = 0; i < this->nCnt; ++i) {
        for(int j = 0; ; ++j) {
            cout<<__getValueFromIntArray2D(this->weight,
                                           this->nCnt,
                                           i,j);
            if(j != (this->nCnt-1)) {
               cout<<" ";
            }else{
                break;
            }
        }
        cout<<endl;
    }
}


}

#endif /* _GRAPH_H_ */

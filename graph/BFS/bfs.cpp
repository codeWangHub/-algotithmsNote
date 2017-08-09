#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/* ============ ���ݽṹ =========== */

/* 1. �ڵ�Ϊbfs���ӵ���Ϣ */
template <class T>
class BfsBase {
private:
    int   distance; /* ����Դ�ڵ�ľ��� */
    int    color;    /* ��ǰ�ڵ����ɫ */
    T*     parent;   /* ǰ�������ڹ��������������� */
public:

    static constexpr int WHITE = 0;
    static constexpr int BLACK = 2;
    static constexpr int GRAY  = 1;

    BfsBase(int d,int c):
       distance(d),color(c),parent(NULL){}

    void setDistance(int d)  { this->distance = d; }
    int getDistance(void) {return this->distance;}

    void setColor(int c) { this->color = c; }
    int  getColor(void) {return this->color;}



    void incDistance(void) {
        this->distance ++;
    }


    void setParent(T& p) {
        this->parent = &p;
    }

    T& getParent(void) {
        return *(this->parent);
    }
};


/* �������ݽṹ */
class Node :public BfsBase<Node>{
private:
    string name;
    int    index;   /* edges�еı�� */
public:

    Node() : BfsBase(0,BfsBase::WHITE) {}
    Node(string name,int index) : BfsBase(0,BfsBase::WHITE),name(name),index(index) {};
    string getName() {return this->name;}
    int getIndex(){return index;}
};



/* ͼ���ݽṹ,�ڽӾ��� */
class Graph {
private:
    Node* nodes;
    int** edges;
    int  nCnt;
    int  eCnt;
public:

    int init(Node* n,int nodeCnt,int** e,int edgeCnt) {
        this->nodes = n;
        this->edges = e;
        this->nCnt = nodeCnt;
        this->eCnt = edgeCnt;
        return 0;
    }

    void show(void) {
        cout<<"there are "<<this->nCnt<<" nodes and "<< this->eCnt <<" edges in this graph."<<endl;
        cout<<"they are :"<<endl;

        for(int i=0;i<this->nCnt;++i) {
            cout<<(this->nodes)[i].getName()<<"-"<<(this->nodes)[i].getIndex()<<" ";
        }
        cout<<endl;
        for(int i=0;i<this->nCnt;++i) {
            for(int j=i;j<this->nCnt;++j) {
                /* ע������һ��Ҫǿ��ת��Ϊint*,������ӱ�������֪�����ָ��ġ���ȡ�Ϊint��4�ֽڣ� */
                if( *((int*)this->edges + 8*i + j )  == 1) {
                    cout<<"("<<(this->nodes)[i].getName()<<","<<(this->nodes)[j].getName()<<")"<<endl;
                }
            }
        }
    }

    /* ֻ��ʾ���뼴�� */
    void showBfsTree(void) {

        for(int i=0;i<this->nCnt; ++i) {
            Node& n = this->getNode(i);
            cout<<"<"<<n.getName()<<","<<n.getDistance()<<">"<<endl;
        }
    }

    Node* getNodes(void) {
        return this->nodes;
    }

    int** getEdges(void) {
        return this->edges;
    }

    int getNodeCnt() {
        return this->nCnt;
    }

    int getEdgeCnt() {
        return this->eCnt;
    }

    Node& getNode(int index) {
        return (this->nodes)[index];
    }

    Node& getNode(string name) {
        for(int i=0;i<this->nCnt;++i) {
               Node& n = this->getNode(i);
            if(n.getName() == name) {
                return n;
            }
        }
        return *(new Node("null",-1));
    }

    bool hasEdge(int i,int j) {
        if( *((int*)(this->edges)  + i*(this->nCnt) + j)  == 1 )
            return true;
        return false;
    }

};





/*
 *  �˹����ϸ��ա��㷨���ۡ�����P344 BFSα����
 */
int bfs(Graph& g,Node& start)
{
    /* ���ĳ�ʼ����������ʱ�ѳ�ʼ�� */
    int index = 0;
    int nodes = g.getNodeCnt();

    /* ��ʼ��һ������ */
    queue<Node>* bfsQueue = new queue<Node>();
    /* ��ʼ��start��Ϊ��ɫ */
    start.setColor(Node::GRAY);   // s.color = GRAY
    bfsQueue->push(start);        // ENQUEUE(Q,s)

    while(!bfsQueue->empty()) {   // while Q != empty
        Node& currentNode = bfsQueue->front();  // u = DEQUEUE(Q)
        bfsQueue->pop();

        index = currentNode.getIndex();
        for(int i=0;i<nodes;i++) {
            if( g.hasEdge(index,i) ) {
                Node& v = g.getNode(i);  // for each v : G.Adj[u]
                if(v.getColor() == Node::WHITE) {    // if v.color = WHITE
                    /* �˽�㻹û�б����� */
                    v.setColor(Node::GRAY);   // v.color = GRAY
                    v.setDistance(currentNode.getDistance() + 1);  // v.d = u.d + 1
                    v.setParent(currentNode);   // v.p = u
                    bfsQueue->push(v);       // ENQUEUE(Q,v)
                }
            }
        }

        currentNode.setColor(Node::BLACK);  // u.color = BLACK
    }

    delete bfsQueue;
    return 0;

}




int main(int argc,char **argv)
{
    /* ͼ���ݲο������㷨���ۡ�����P345 ͼ22-3(a) */
    /* �����Ϣ */
    Node nodes[]={
            Node("r",0),Node("v",1),Node("s",2),
            Node("w",3),Node("t",4),Node("x",5),
            Node("u",6),Node("y",7)};

    /* ����Ϣ */
     int edges[8][8] = {
            /*   r  v  s  w  t  x  u  y  */
        /*r*/   {0, 1, 1, -1,-1,-1,-1,-1 },
        /*v*/   {1, 0,-1, -1,-1,-1,-1,-1 },
        /*s*/   {1,-1, 0,  1,-1,-1,-1,-1 },
        /*w*/   {-1,-1,1,  0, 1, 1,-1,-1 },
        /*t*/   {-1,-1,-1, 1, 0, 1, 1,-1 },
        /*x*/   {-1,-1,-1, 1, 1, 0, 1, 1 },
        /*u*/   {-1,-1,-1,-1, 1, 1, 0, 1 },
        /*y*/   {-1,-1,-1,-1,-1, 1, 1, 0 }
            };

    /* Graph ���� */
    Graph g;
    g.init(nodes,8,(int**)&edges[0][0],10);

    g.show();

    bfs(g,g.getNode("s"));
    cout<<"==========================="<<endl;
    g.showBfsTree();

    return 0;
}

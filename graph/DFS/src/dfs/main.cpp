#include <iostream>
#include "../Node.h"
#include "../Graph.h"

using namespace std;
using codewang::Node;
using codewang::Graph;


int time = 0;

void dfs_visit(Graph<Node>& graph,Node& n)
{
    time++;
    n.setColor(Node::GRAY);
    cout<<"set "<<n.getName()<<"'s color = GRAY"<<endl;
    n.setDiscoverTime(time);

    auto b = graph.getAdj(n).begin() ,
         e = graph.getAdj(n).end();


    for( b++;b != e; b++) {
        if( (*b)->getColor() == Node::WHITE ) {
            cout<<"find a new vertex : " << (*b)->getName()<<endl;
            (*b)->setParent(n);
            dfs_visit(graph,*(*b));
        }else{
            cout<<"vertex : "<<(*b)->getName()<<" is not WHITE."<<endl;
        }
    }

    n.setColor(Node::BLACK);
    cout<<n.getName()<<" is over"<<endl;
    time++;
    n.setFinishTime(time);
}

int dfs(Graph<Node>& graph)
{
    vector<Node*>& nodes = graph.getNodes();

    for(auto b = nodes.begin(), e = nodes.end(); b != e; ++b) {
        if( (*b)->getColor() == Node::WHITE ) {
            dfs_visit(graph,*(*b));
        }
    }
    return 0;
}









int main()
{

    Node nodes[]= {
        Node("u"),
        Node("v"),
        Node("w"),
        Node("x"),
        Node("y"),
        Node("z")
    };

    int edges[6][6] = {
       { 0, 1,-1, 1,-1,-1},
       {-1, 0,-1,-1, 1,-1},
       {-1,-1, 0,-1, 1, 1},
       {-1, 1,-1, 0,-1,-1},
       {-1,-1,-1, 1, 0,-1},
       {-1,-1,-1,-1,-1, 1}
    };



    Graph<Node> g((Node*)nodes,6,(int**)edges);

    dfs(g);

    g.showNodes();

    return 0;
}

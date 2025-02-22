#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Kosaraju-Sharir algorithm
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    stack<T> nodes;
    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
    }
    for (Vertex<T>* u : g->getVertexSet()) {
        if (!u->isVisited())
            dfs_SCC(u,nodes);
    }

    Graph<T> reversed = Transpose(g);

    while (!nodes.empty()) {
        T infoVertex = nodes.top();
        nodes.pop();

        Vertex<T>* vertex = reversed.findVertex(infoVertex);
        if (!vertex->isVisited()) {
            vector<T> scc;
            create_SCCs(vertex, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

template <typename T>
void dfs_SCC(Vertex<T>* v, stack<T>& nodes) {
    v->setVisited(true);
    for (Edge<T>* u : v->getAdj()) {
        Vertex<T>* dest = u->getDest();
        if (!dest->isVisited()) {
            dfs_SCC(dest,nodes);
        }
    }
    nodes.push(v->getInfo());
}

template <typename T>
Graph<T> Transpose(Graph<T>* g) {
    Graph<T> transposed;

    for (Vertex<T>* v : g->getVertexSet()) {
        transposed.addVertex(v->getInfo());
    }

    for (Vertex<T>* v : g->getVertexSet()) {
        for (Edge<T>* u : v->getAdj()) {
            transposed.addEdge(u->getDest()->getInfo(), u->getOrig()->getInfo(),u->getWeight());
        }
    }
    return transposed;
}


template <typename T>
void create_SCCs(Vertex<T>*v, vector<T>& scc) {
    scc.push_back(v->getInfo());
    v->setVisited(true);
    for (Edge<T>* u : v->getAdj()) {
        Vertex<T>* dest = u->getDest();
        if (!dest->isVisited()) {
            create_SCCs(dest, scc);
        }
    }
}



#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;

/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
*/


template <typename T>
void calc_indegree(Graph<T> *g) {
    for (Vertex<T>* v : g->getVertexSet()) {
        v->setIndegree(0);
        v->setVisited(false);
    }
    for (Vertex<T>* v : g->getVertexSet()) {
        for (Edge<T>* w : v->getAdj()) {
            Vertex<T>* i = w->getDest();
            i->setIndegree(i->getIndegree()+1);
        }
    }
}


template <typename T>
vector<T> topsort(Graph<T> *g) {
    vector<int> res;
    calc_indegree(g);
    queue<Vertex<T>*> q;
    for (Vertex<T>* v : g->getVertexSet()) {
        if (v->getIndegree() == 0) q.push(v);
    } // push all vertices with indegree 0
    while (!q.empty()) {
        Vertex<T>* u = q.front();
        q.pop();
        res.push_back(u->getInfo());
        for (Edge<T>* w : u->getAdj()) {
            Vertex<T>* i = w->getDest();
            i->setIndegree(i->getIndegree() - 1);
            if (i->getIndegree() == 0) q.push(i);
        }
    }
    /*if (res.size() != g->getVertexSet().size()) {
        res = {};
    }*/
    return res;
}


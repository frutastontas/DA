// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include "../data_structures/Graph.h"

// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    if (!w->isVisited() && residual>0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue< Vertex<T> *> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        Vertex<T> *v = q.front();
        q.pop();
        for (auto w : v->getAdj()) { //test outgoing edges
            testAndVisit(q,w,w->getDest(),w->getFlow());
        }
        for (auto w: v->getIncoming()) { //test incoming edges
            testAndVisit(q,w,w->getOrig(),w->getFlow());
        }
    }

   return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    for (auto v = t; v!=s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f=std::min(f,e->getWeight()-e->getFlow());
            v= e->getOrig();
        }else {
            f= std::min(f,e->getFlow());
            v= e->getDest();
        }
    }
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    for (auto v=t; v!=s;) {
        auto e=v->getPath();
        auto flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow+f);
            v= e->getOrig();
        }else {
            e->setFlow(flow-f);
            v= e->getDest();
        }
    }
}

// Function implementing the Edmonds-Karp algorithm
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    auto s = g->findVertex(source);
    auto t = g->findVertex(target);

    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    while (findAugmentingPath(g,s,t)) {
        auto f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex5, test_edmondsKarp) {
    Graph<int> myGraph;

    for(int i = 1; i <= 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);

    edmondsKarp(&myGraph, 1, 6);

    std::stringstream ss;
    for(auto v : myGraph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());

}
// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"
#include <algorithm>

/**
 * Auxiliary function to set the "path" field to make a spanning tree.
 */
template <typename T>
void dfsKruskalPath(Vertex<T> *v) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        if (e->isSelected() && !e->getDest()->isVisited()) {
            e->getDest()->setPath(e);
            dfsKruskalPath(e->getDest());
        }
    }
}

template <typename T>
bool sortEdges(Edge<T> *v1, Edge<T> *v2) {
    return v1->getWeight() < v2->getWeight();
}

template <typename T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    UFDS ufds(g->getVertexSet().size());
    {
        int id =0;
        for (auto u : g->getVertexSet()) {
            u->setInfo(id++);
        }
    }

    std::vector<Edge<T>*> edges;
    for (Vertex<T> *v : g->getVertexSet()) {
        for (Edge<T> *e : v->getAdj()) {
            e->setSelected(false);
            edges.push_back(e);
        }
    }
    sort(edges.begin(), edges.end(), [](Edge<T> *v1, Edge<T> *v2)->bool{return v1->getWeight() < v2->getWeight();});
    for (Edge<T>* e: edges) {
        Vertex<T> * org = e->getOrig();
        Vertex<T>* dest = e->getDest();
        if (!ufds.isSameSet(org->getInfo(), dest->getInfo())) {
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            ufds.linkSets(org->getInfo(), dest->getInfo());
        }
    }
    for (auto v: g->getVertexSet()) {
        v->setVisited(false);
    }
    g->getVertexSet()[0]->setPath(nullptr);
    dfsKruskalPath(g->getVertexSet()[0]);
    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

TEST(TP3_Ex2, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}

TEST(TP3_Ex2_performance, test_performance_kruskal) {
    //Change these const parameters as needed
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 30; //Try with 100
    const int STEP_SIZE = 10;
    const int N_REPETITIONS = 50;
    for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Graph<int> g;
        generateRandomGridGraph(n, g);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= N_REPETITIONS; i++)
            kruskal(&g);
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << "Processing grid (Kruskal) " << n << " x " << n << " average time (milliseconds)=" << (elapsed / N_REPETITIONS) << std::endl;
    }
}

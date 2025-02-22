#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
vector<vector<T>> sccTarjan(Graph<T>* g) {
    vector<vector<T>> res;

    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
        v->setLow(0);
        v->setNum(0);
    }
    int counter =1;
    stack<T> s;

    for (Vertex<T>* v : g->getVertexSet()) {
        if (!v->isVisited()) DFSaux(v,counter,s,res);
    }
    return res;
}


template <typename T>
void DFSaux(Vertex<T> *v, int &counter, stack<T> &st, vector<vector<T>> &sccs) {
    v->setVisited(true);
    v->setLow(counter);
    v->setNum(counter);
    counter++;
    st.push(v->getInfo());
    for (Edge<T>* u: v->getAdj()) {
        Vertex<T>* dest = u->getDest();
        if (!dest->isVisited()) {
            DFSaux(dest,counter,st,sccs);
            v->setLow(min(v->getLow(),dest->getLow()));
        }else {
            v->setLow(min(v->getLow(),dest->getNum()));
        }
    }
    if (v->getNum() == v->getLow()) {
        vector<T> scc;
        T value;
        do{
            value = st.top();
            scc.push_back(value);
            st.pop();
        }while (v->getInfo() != value);

        sccs.push_back(scc);
    }
}
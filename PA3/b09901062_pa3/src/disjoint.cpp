#include "graph.h"

DisjoinSet::DisjoinSet(int &n) : nSubset_(n) {
    subs_ = new subset[n];
    makeSet();
}

DisjoinSet::~DisjoinSet() {
    delete[] subs_;
}

//  Implement functions of disjoint set: makeset, find, union
void DisjoinSet::makeSet() {
    for (uint32_t i = 0; i < nSubset_; ++i) {
        subs_[i].parent = i;
        subs_[i].rank = 0;
    }
}

int DisjoinSet::find(int &i) const {
    if (subs_[i].parent == i)
        return i;
    else
        return find(subs_[i].parent);
}

void DisjoinSet::Union(int &i, int &j) {
    int iRepresent = find(i);
    int jRepresent = find(j);
    if (subs_[iRepresent].rank < subs_[jRepresent].rank)
        subs_[iRepresent].parent = jRepresent;
    else if (subs_[iRepresent].rank > subs_[jRepresent].rank)
        subs_[jRepresent].parent = iRepresent;
    else {
        subs_[jRepresent].parent = iRepresent;
        subs_[iRepresent].rank++;
    }
}
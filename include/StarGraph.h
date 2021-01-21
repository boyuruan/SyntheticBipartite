#ifndef STARGRAPH_INCLUDED
#define STARGRAPH_INCLUDED

#include "headers.h"

struct hash_pair {
    template <class T1, class T2> size_t operator()(const pair<T1, T2> &p) {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);
        return h1 ^ h2;
    }
};

class StarGraph {
private:
    long long edgeNumber{0};
    int largeEdge{0};
    vector<vector<long long>> e;
    unordered_map<long long, pair<int, int>> edgeIDEndpointMap;

public:
    StarGraph() {}

    StarGraph(int l) : largeEdge(l) {}

    void generate_graph();
};

#endif
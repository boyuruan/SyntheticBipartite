#ifndef STARGRAPH_INCLUDED
#define STARGRAPH_INCLUDED

#include "headers.h"

#define MAXN 2000000000
#define MAXN1 1000000000
#define INC_FACTOR 1.2

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
    long long largeEdge{0};
    int largeThres{0};
    int smallThres{0};
    vector<int> bfs;
    vector<vector<long long>> e;
    unordered_map<long long, pair<long long, long long>> edgeIDEndpointMap;

public:
    StarGraph() {}

    StarGraph(int l) : largeEdge(l) {}

    StarGraph(int l, int lt, int st)
        : largeEdge(l), largeThres(lt), smallThres(st) {}

    void generate_graph();

    void generate_star();

    void output_graph(char *file);

    void assessment();
};

class IntNode {
public:
    int val, id;
    bool operator<(const IntNode &node) const;
};

#endif
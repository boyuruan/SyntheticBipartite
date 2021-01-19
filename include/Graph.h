#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED

#include "headers.h"

class Graph {
private:
    int n1{0};
    int n2{0};
    int bloomSize{0};
    int overLap{0};
    double prob{1.0};
    vector<int> *bloom_vertex{nullptr};

public:
    Graph() {}

    Graph(int _n1, int _n2, int _bloomSize, int _overLap, double _prob)
        : n1(_n1), n2(_n2), bloomSize(_bloomSize), overLap(_overLap),
          prob(_prob) {}

    void generate_graph();

    void output_graph(char *file);
};

#endif
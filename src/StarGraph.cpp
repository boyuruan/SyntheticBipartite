#include "StarGraph.h"

//#define DEBUG

void StarGraph::generate_graph() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<> dis_large((int)floor(0.8 * largeThres),
                                         largeThres);
    uniform_int_distribution<> dis_small((int)floor(0.5 * smallThres),
                                         smallThres);
    uniform_int_distribution<long long> dis_edge(0, 1);
    long long i = 0;
    for (; i < largeEdge; i++) {
        bfs.push_back(dis_large(gen));
        vector<long long> tmp;
        tmp.push_back(i);
        e.push_back(tmp);
        edgeNumber++;
        edgeIDEndpointMap[i] = make_pair(i, i);
    }
    for (long long w = 0; w < largeEdge; w++) {
        for (int j = 0; j < bfs[w]; j++) {
            vector<long long> tmp;
            tmp.push_back(i);
            e.push_back(tmp);
            edgeIDEndpointMap[edgeNumber] = make_pair(i, i);
#ifdef DEBUG
            if (edgeNumber == 11727) {
                int m = 0;
            }
#endif
            bfs.push_back(1);
            edgeNumber++;
            e[w].push_back(i);
            edgeIDEndpointMap[edgeNumber] = make_pair(w, i);
#ifdef DEBUG
            if (edgeNumber == 11727) {
                int m = 0;
            }
#endif
            bfs.push_back(1);
            edgeNumber++;
            e[i].push_back(w);
            edgeIDEndpointMap[edgeNumber] = make_pair(i, w);
#ifdef DEBUG
            if (edgeNumber == 11727) {
                int m = 0;
            }
#endif
            bfs.push_back(1);
            edgeNumber++;
            i++;
        }
    }
    printf("%lu\n", edgeIDEndpointMap.size());
    i = largeEdge;
    long long end = largeEdge + 3 * bfs[0];
    dis_edge.param(
        uniform_int_distribution<long long>::param_type(end, edgeNumber - 1));
    for (long long w = 0; w < largeEdge - 1; w++) {
        for (; i < end; i++) {
            int B = dis_small(gen);
            if (B <= bfs[i]) {
                continue;
            } else {
                for (int t = 0; t < B - bfs[i]; t++) {
                    long long eid = dis_edge(gen);
                    pair<long long, long long> e1 = edgeIDEndpointMap[i];
                    pair<long long, long long> e2 = edgeIDEndpointMap[eid];
                    bfs[i]++;
                    bfs[eid]++;
                    e[e1.first].push_back(e2.second);
                    edgeIDEndpointMap[edgeNumber] =
                        make_pair(e1.first, e2.second);
                    bfs.push_back(1);
                    edgeNumber++;
                    e[e2.first].push_back(e1.second);
                    edgeIDEndpointMap[edgeNumber] =
                        make_pair(e2.first, e1.second);
                    edgeNumber++;
                }
            }
        }
        end += bfs[w + 1];
        long long original_b = dis_edge.b();
        dis_edge.param(
            uniform_int_distribution<long long>::param_type(end, original_b));
        // printf("%lu\n", edgeIDEndpointMap.size());
    }

    printf("%lld edges in total.\n", edgeNumber);
}

void StarGraph::output_graph(char *file) {
    string filename = string(file) + "/graph.txt";
    FILE *f = fopen(filename.c_str(), "w");
    fprintf(f, "%\n%\n");
    for (long long i = 0, size = e.size(); i < size; i++) {
        for (long long j = 0, psize = e[i].size(); j < psize; j++) {
            fprintf(f, "%lld\t%lld\n", i, e[i][j]);
        }
    }
    fclose(f);
}
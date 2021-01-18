#include "Graph.h"

void Graph::generate_graph() {
    if (n1 > n2) {
        swap(n1, n2);
    }
    int bloomCnt = n1 * (n1 - 1) / 2;
    bloom_vertex = new vector<int>[bloomCnt];
    vector<int> sizes(bloomCnt, bloomSize);
    vector<int> uses(n2, overLap);
    vector<int> remaining_vertex;
    remaining_vertex.resize(n2);
    for (int i = 0; i < n2; i++) {
        remaining_vertex.push_back(i);
    }
    vector<int> remaining_bloom;
    remaining_bloom.reserve(bloomCnt);
    for (int i = 0; i < bloomCnt; i++) {
        remaining_bloom.push_back(i);
    }
    uniform_int_distribution<> dis_bloom(0, bloomCnt - 1);
    uniform_int_distribution<> dis_vertex(0, n2 - 1);
    random_device rd;
    mt19937 g(rd());
    unordered_set<int> uset;
    shuffle(remaining_vertex.begin(), remaining_vertex.end(), g);
    while (bloomCnt != 0 && n2 != 0) {
        int index = dis_bloom(g);
        int bid = remaining_bloom[index];
        if (remaining_vertex.size() <= sizes[bid]) {
            for (int j = 0; j < remaining_vertex.size();) {
                int eid = remaining_vertex[j];
                uses[eid]--;
                if (uses[eid] == 0) {
                    n2--;
                    if (j == remaining_vertex.size() - 1) {
                        remaining_vertex.pop_back();
                    } else {
                        swap(remaining_vertex[j], remaining_vertex.back());
                        remaining_vertex.pop_back();
                    }
                } else {
                    j++;
                }
                sizes[bid]--;
                bloom_vertex[bid].push_back(eid);
            }
        } else if (remaining_vertex.size() <= 5 * sizes[bid]) {
            vector<int> vertex_to_add;
            vertex_to_add.reserve(sizes[bid]);
            vector<int> tmp;
            tmp.resize(remaining_vertex.size());
            for (int i = 0; i < remaining_vertex.size(); i++) {
                tmp[i] = i;
            }
            for (int i = 0; i < sizes[bid]; i++) {
                int r = rand() % tmp.size();
                vertex_to_add.push_back(tmp[r]);
                if (r != tmp.size() - 1) {
                    swap(tmp[r], tmp.back());
                }
                tmp.pop_back();
            }
            tmp.clear();
            tmp.shrink_to_fit();
                }
        bloomCnt--;
        if (index == remaining_bloom.size() - 1) {
            remaining_bloom.pop_back();
        } else {
            swap(remaining_bloom[index], remaining_bloom.back());
            remaining_bloom.pop_back();
        }
        dis_bloom.param(
            uniform_int_distribution<>::param_type(0, bloomCnt - 1));
        dis_vertex.param(uniform_int_distribution<>::param_type(0, n2 - 1));
    }
}
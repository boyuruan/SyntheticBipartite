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
    remaining_vertex.reserve(n2);
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
    unordered_map<int, int> umap;
//    shuffle(remaining_vertex.begin(), remaining_vertex.end(), g);
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
                vertex_to_add.push_back(remaining_vertex[tmp[r]]);
                umap.insert(make_pair(remaining_vertex[tmp[r]], tmp[r]));
                if (r != tmp.size() - 1) {
                    swap(tmp[r], tmp.back());
                }
                tmp.pop_back();
            }
            tmp.clear();
            tmp.shrink_to_fit();
            for (int i = 0; i < vertex_to_add.size(); i++) {
                int eid = remaining_vertex[vertex_to_add[i]];
                int index = umap[eid];
                uses[eid]--;
                if (uses[eid] == 0) {
                    n2--;
                    if (index != remaining_vertex.size() - 1) {
                        swap(remaining_vertex[index], remaining_vertex.back());
                        auto it = umap.find(remaining_vertex[index]);
                        if (it != umap.end()) {
                            umap[remaining_vertex[index]] = index;
                        }
                    }
                    umap.erase(eid);
                    remaining_vertex.pop_back();
                }
                sizes[bid]--;
                bloom_vertex[bid].push_back(eid);
            }
            umap.clear();
            vertex_to_add.clear();
            vertex_to_add.shrink_to_fit();
        } else {
            vector<int> vertex_to_add;
            vertex_to_add.reserve(sizes[bid]);
            for (int i = 0; i < sizes[bid]; i++) {
                int r = dis_vertex(g);
                while (uset.count(r) != 0) {
                    r = dis_vertex(g);
                }
                uset.insert(r);
                umap.insert(make_pair(remaining_vertex[r], r));
                vertex_to_add.push_back(remaining_vertex[r]);
            }
            for (int i = 0; i < vertex_to_add.size(); i++) {
                int eid = remaining_vertex[vertex_to_add[i]];
                int index = umap[eid];
                uses[eid]--;
                if (uses[eid] == 0) {
                    n2--;
                    if (index != remaining_vertex.size() - 1) {
                        swap(remaining_vertex[index], remaining_vertex.back());
                        auto it = umap.find(remaining_vertex[index]);
                        if (it != umap.end()) {
                            umap[remaining_vertex[index]] = index;
                        }
                    }
                    umap.erase(eid);
                    remaining_vertex.pop_back();
                }
                sizes[bid]--;
                bloom_vertex[bid].push_back(eid);
            }
            umap.clear();
            uset.clear();
            vertex_to_add.clear();
            vertex_to_add.shrink_to_fit();
        }
        bloomCnt--;
        if (index == remaining_bloom.size() - 1) {
            remaining_bloom.pop_back();
        } else {
            swap(remaining_bloom[index], remaining_bloom.back());
            remaining_bloom.pop_back();
        }
        if (bloomCnt != 0)
            dis_bloom.param(
                uniform_int_distribution<>::param_type(0, bloomCnt - 1));
        if (n2 != 0)
            dis_vertex.param(uniform_int_distribution<>::param_type(0, n2 - 1));
    }
}

void Graph::output_graph(char* file) {
    ofstream fout;
    string graph_file = string(file) + "/graph.txt";
    fout.open(graph_file.c_str(), ios::out);
    fout << "%\n%\n";
    int u = 0, v = 1;
    int bloomCnt = n1 * (n1 - 1) / 2;
    for (int i = 0; i < bloomCnt; i++) {
        for (int j = 0; j < bloom_vertex[i].size(); j++) {
            fout << u << '\t' << bloom_vertex[i][j] << endl;
            fout << v << '\t' << bloom_vertex[i][j] << endl;
        }
        v++;
        if (v == n1) {
            u++;
            v = u + 1;
        }
    }
    fout.close();
}
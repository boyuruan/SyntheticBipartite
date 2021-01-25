#include "StarGraph.h"

//#define DEBUG

bool IntNode::operator<(const IntNode &node) const {
    if (val == node.val) {
        return id < node.id;
    } else {
        return val < node.val;
    }
}

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
    // printf("%lu\n", edgeIDEndpointMap.size());
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
    // for (long long j = 0, size = e.size(); j < size; j++) {
    //     sort(e[j].begin(), e[j].end());
    // }

    // printf("%lld edges in total.\n", edgeNumber);
    // edgeIDEndpointMap.clear();
}

void StarGraph::output_graph(char *file) {
    string filename = string(file) + "/graph.txt";
    FILE *f = fopen(filename.c_str(), "w");
    fprintf(f, "%%\n%%\n");
    for (long long i = 0, size = e.size(); i < size; i++) {
        for (long long j = 0, psize = e[i].size(); j < psize; j++) {
            fprintf(f, "%lld\t%lld\n", i, e[i][j]);
        }
    }
    fclose(f);
}

void StarGraph::generate_star() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<> dis_small((int)(0.5 * smallThres), smallThres);
    bfs.push_back(largeThres);
    vector<long long> tmp;
    tmp.push_back(0);
    e.push_back(tmp);
    int idx_vertex = 1;
    for (int i = 0; i < largeThres; i++) {
        vector<long long> tmp;
        tmp.push_back(idx_vertex);
        e.push_back(tmp);
        bfs.push_back(1);
        e[0].push_back(idx_vertex);
        bfs.push_back(1);
        e[idx_vertex].push_back(0);
        bfs.push_back(1);
        idx_vertex++;
    }
    long long idx_edge = 1;
    int n1 = idx_vertex;
    for (int i = 1; i < n1; i++) {
        int B = dis_small(gen);
        if (B > bfs[idx_edge]) {
            for (int j = 0; j < B - bfs[idx_edge++]; j++) {
                vector<long long> tmp;
                tmp.push_back(idx_vertex);
                e.push_back(tmp);
                e[i].push_back(idx_vertex);
                e[idx_vertex].push_back(i);
                idx_vertex++;
            }
        }
        B = dis_small(gen);
        if (B > bfs[idx_edge]) {
            for (int j = 0; j < B - bfs[idx_edge++]; j++) {
                vector<long long> tmp;
                tmp.push_back(idx_vertex);
                e.push_back(tmp);
                e[0].push_back(idx_vertex);
                e[idx_vertex].push_back(i);
                idx_vertex++;
            }
        }
        B = dis_small(gen);
        if (B > bfs[idx_edge]) {
            for (int j = 0; j < B - bfs[idx_edge++]; j++) {
                vector<long long> tmp;
                tmp.push_back(idx_vertex);
                e.push_back(tmp);
                e[i].push_back(idx_vertex);
                e[idx_vertex].push_back(0);
                idx_vertex++;
            }
        }
    }
}

void StarGraph::assessment() {
    int n1 = e.size();
    int n2 = n1;
    int n = n1 + n2;
    int a, b;
    long long m = 0;
    vector<int> *conj = new vector<int>[n];
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < e[i].size(); j++) {
            a = i;
            b = e[i][j] + n1;
            if (conj[a].capacity() == conj[a].size()) {
                conj[a].reserve(conj[a].size() * INC_FACTOR);
            }
            if (conj[b].capacity() == conj[b].size()) {
                conj[b].reserve(conj[b].size() * INC_FACTOR);
            }
            conj[a].push_back(b);
            conj[b].push_back(a);
        }
    }
    int maxd = 0;
    for (int i = 0; i < n; ++i) {
        if (conj[i].size() > 0) {
            sort(conj[i].begin(), conj[i].end());
            int p = 1;
            for (int j = 1; j < (int)conj[i].size(); ++j)
                if (conj[i][j - 1] != conj[i][j])
                    conj[i][p++] = conj[i][j];
            conj[i].resize(p);
            m += p;
            maxd = max(maxd, p);
        }
    }
    int *oid = new int[n], *nid = new int[n];
    IntNode *f = new IntNode[n];
    for (int i = 0; i < n; i++) {
        f[i].id = i;
        f[i].val = (int)conj[i].size();
    }
    sort(f, f + n);
    for (int i = 0; i < n; i++) {
        oid[i] = f[n - 1 - i].id;
    }
    delete[] f;
    f = nullptr;
    for (int i = 0; i < n; i++) {
        nid[oid[i]] = i;
    }
    int *deg = new int[n];
    for (int i = 0; i < n; i++) {
        deg[i] = (int)conj[oid[i]].size();
    }
    int **ed = new int *[n];
    int **con = new int *[n];
    for (int i = 0; i < n; i++) {
        int u = oid[i], d = (int)conj[u].size();
        con[i] = new int[d];
        for (int j = 0; j < d; j++) {
            con[i][j] = nid[conj[u][j]];
        }
        sort(con[i], con[i] + d);
    }
    int **cnt = new int *[n];
    int *cnt_dat = new int[m];
    memset(cnt_dat, 0, sizeof(int) * m);
    long long p = 0;
    for (int i = 0; i < n; i++) {
        cnt[i] = cnt_dat + p;
        p += deg[i];
    }
    long long cnt_rec = 0, cnt_tmp = 0, cnt_bistar = 0;
    m /= 2;
    int *cnt_e = new int[m];
    int *wing_e = new int[m];
    memset(cnt_e, 0, sizeof(int) * m);
    memset(wing_e, 0, sizeof(int) * m);
    vector<int> cnt_star;
    vector<vector<int>> edge_con(m);
    vector<vector<int>> edge_sibling(m);
    vector<vector<int>> star_con;
    for (int i = 0; i < n; i++) {
        ed[i] = new int[deg[i]];
    }
    int idx_edge = 0, idx_star = 0;
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < deg[u]; i++) {
            int v = con[u][i];
            if (u < v) {
                ed[u][i] = idx_edge++;
            } else {
                int l = 0, r = deg[v] - 1, mid = 0;
                while (l < r) {
                    mid = l + (r - l) / 2;
                    if (con[v][mid] < u) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }
                }
                ed[u][i] = ed[v][l];
            }
        }
    }

    int u, v, w;
    int *last_use = new int[n], *last_cnt = new int[n], *visited_w = new int[n],
        pre = 0;
    memset(last_use, -1, sizeof(int) * n);
    memset(visited_w, -1, sizeof(int) * n);
    memset(last_cnt, 0, sizeof(int) * n);
    int idx = 0;
    for (u = 0; u < n; u += 1) {
        for (int j = 0; j < idx; j++) {
            last_cnt[last_use[j]] = 0;
            visited_w[last_use[j]] = -1;
        }
        idx = 0;
        for (int i = 0; i < deg[u]; ++i) {
            v = con[u][i];
            pre = -1;
            for (int j = 0; j < deg[v]; ++j) {
                w = con[v][j];
                if (w >= u || w >= v)
                    break;
                cnt_rec += last_cnt[w];
                ++last_cnt[w];
                if (last_cnt[w] == 1)
                    last_use[idx++] = w;
            }
        }
        // if( !cnt_edge ) continue;
        for (int i = 0; i < deg[u]; ++i) {
            v = con[u][i];
            for (int j = 0; j < deg[v]; ++j) {
                w = con[v][j];
                if (w >= u || w >= v)
                    break;
                // int dlt = last_cnt[w] * (last_cnt[w] - 1) / 2;
                int dlt = last_cnt[w] - 1;
                if (dlt) {
                    cnt[u][i] += dlt;
                    //#pragma omp atomic
                    cnt[v][j] += dlt;
                } else
                    continue;
                if (visited_w[w] == -1) {
                    edge_con[ed[u][i]].push_back(idx_star);
                    edge_con[ed[v][j]].push_back(idx_star);
                    vector<int> tmp;
                    star_con.push_back(tmp);
                    star_con[idx_star].push_back(ed[u][i]);
                    star_con[idx_star].push_back(ed[v][j]);
                    edge_sibling[ed[u][i]].push_back(ed[v][j]);
                    edge_sibling[ed[v][j]].push_back(ed[u][i]);
                    // int tmp_dlt = dlt * (dlt-1) / 2;
                    cnt_star.push_back(dlt);
                    visited_w[w] = idx_star++;
                } else {
                    edge_con[ed[u][i]].push_back(visited_w[w]);
                    edge_con[ed[v][j]].push_back(visited_w[w]);
                    star_con[visited_w[w]].push_back(ed[u][i]);
                    star_con[visited_w[w]].push_back(ed[v][j]);
                    edge_sibling[ed[u][i]].push_back(ed[v][j]);
                    edge_sibling[ed[v][j]].push_back(ed[u][i]);
                }
            }
        }
    }
    delete[] last_use;
    delete[] last_cnt;
    delete[] visited_w;
    printf("n: %d\n", n);
    printf("m: %d\n", idx_edge);
    printf("n_rectangles: %lld\n", cnt_rec);

    int max_btf_e = 0;
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < deg[u]; i++) {
            cnt_e[ed[u][i]] += cnt[u][i];
            if (max_btf_e < cnt_e[ed[u][i]]) {
                max_btf_e = cnt_e[ed[u][i]];
            }
        }
    }
    cout << "max btf_e: " << max_btf_e << endl;
    cout << "total number of bi-star: " << idx_star << endl;
    long long min_deg = 0;
    for (u = 0; u < n; ++u) {
        for (int i = 0; i < deg[u]; ++i) {
            int v = con[u][i];
            if (u < v) {
                min_deg += min(deg[u], deg[v]);
            }
        }
    }
    cout << "sum of min degree: " << min_deg << endl;
    cout << "log(m): " << log(m * 1.0) << endl;
    cout << "complexity: " << min_deg * log(m * 1.0) << endl;
    cout << "ratio: " << cnt_rec / min_deg / log(m * 1.0) << endl;
}
#ifndef XUE_H
#define XUE_H

#include "heads.h"

struct node {
    eletype value;
    int index;
    bool operator <(const node &x)const
    {
        return x.value < value;
    }
};
vector<int> pre;
vector<vector<eletype> > w_M;

void pre_compute(vector<vector<vector<eletype> > > w, vector<eletype> c, int n) {
    eletype W = 0;
    for (int i = 0; i < K; i++)
        if (W < c[i]) W = c[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < K; k++)
                w[i][j][k] = w[i][j][k] * W / c[k];
    w_M.clear(); w_M.resize(n);
    for (int i = 0; i < n; i++) {
        w_M[i].resize(n);
        for (int j = 0; j < n; j++) {
            w_M[i][j] = 0;
            for (int k = 0; k < K; k++)
                if (w_M[i][j] < w[i][j][k]) w_M[i][j] = w[i][j][k];
            w_M[i][j] /= W;
        }
    }
}

int dij_heap(vector<vector<eletype> > w, int n, int s, int t) {
    priority_queue<node> q;
    vector<eletype> dis, f;
    dis.clear(); dis.resize(n);
    f.clear(); f.resize(n);
    pre.clear(); pre.resize(n);
    for (int i = 0; i < n; i++) {
        dis[i] = Inf;
        f[i] = 0;
    }
    dis[s] = 0;
    q.push((node){0, s});
    for (int i = 1; i < n; i++) {
        if (q.empty()) break;
        int u = q.top().index;
        if (f[u]) continue; f[u] = 1;
        for (int v = 0; v < n; v++) {
            if (dis[v] > dis[u] + w[u][v]) {
                dis[v] = dis[u] + w[u][v];
                q.push((node){dis[v], v});
                pre[v] = u;
            }
        }
        q.pop();
    }
    // printf("%f\n", dis[t]);
    if (dis[t] != Inf) return 1;
    return 0;
}

#endif //XUE_H
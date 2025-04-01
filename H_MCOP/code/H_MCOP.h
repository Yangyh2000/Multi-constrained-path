#ifndef H_MCOP_H
#define H_MCOP_H

#include "heads.h"
#include "FibHeap.h"

vector<eletype> r, g, C;
vector<vector<eletype> > R, G;

int Prefer_the_best(int v, eletype Ctmp, eletype gtmp, vector<eletype> Gtmp, vector<eletype> Rtmp,vector<eletype> c) {
    if (Ctmp < C[v]) {
        int flag = 1;
        for (int k = 0; k < K; k++)
            flag &= Gtmp[k] + Rtmp[k] < c[k];
        if (flag) return 1;
    }
    if (Ctmp > C[v]) {
        int flag = 1;
        for (int k = 0; k < K; k++)
            flag &= G[v][k] + R[v][k] < c[k];
        if (flag) return 0;
    }
    if (gtmp < g[v]) return 1;
    return 0;
}

void reserve_dij(vector<vector<vector<eletype> > > w, vector<eletype> c, vector<eletype> &pre_r, int n, int t) {
    vector<int> visited(n);
    CFibHeap *hb = new CFibHeap();
    visited[t] = 1;
    r.clear();
    R.clear();
    r.resize(n);
    R.resize(n);
    for (int i = 0; i < n; i++) {
        R[i].resize(K);
        r[i] = Inf;
    }
    r[t] = 0;
    hb->fibHeapInsert(t, r[t]);
    for (int i = 1; i < n; i++) {
        //提取最小节点
        SFibHeapNode *node = hb->extractMinNode();
        if (node == NULL) break;
        int v = node->name;
        visited[v] = 1;
        //松弛
        for (int u = 0; u < n; u++) {
            eletype temp = 0;
            for (int k = 0; k < K; k++)
                temp += (R[v][k] + w[u][v][k]) / c[k];
            if (visited[u] == 0 && w[u][v][0] != Inf && r[u] > temp) {
                hb->fibHeapInsert(u, temp);
                r[u] = temp;
                for (int k = 0; k < K ; k++)
                    R[u][k] = R[v][k] + w[u][v][k];
                pre_r[v] = u;
            }
        }
    }    
}

void look_ahead_dij(vector<vector<vector<eletype> > > w, vector<eletype> c, vector<eletype> &pre_g, int n, int s) {
    vector<int> visited(n);
    CFibHeap *hb = new CFibHeap();
    visited[s] = 1;
    g.clear(); G.clear(); C.clear();
    g.resize(n); G.resize(n); C.resize(n);
    for (int i = 0; i < n; i++) {
        G[i].resize(K);
        g[i] = Inf; C[i] = Inf;
    }
    g[s] = 0; C[s] = 0;
    hb->fibHeapInsert(s, g[s]);
    for (int i = 1; i < n; i++) {
        //提取最小节点
        SFibHeapNode *node = hb->extractMinNode();
        if (node == NULL) break;
        int u = node->name;
        visited[u] = 1;
        //松弛
        for (int v = 0; v < n; v++) {
            eletype Ctmp = C[u] + w[u][v][0], gtmp = 0;
            vector<eletype> Gtmp, Rtmp;
            Gtmp.resize(K);
            Rtmp.resize(K);
            for (int k = 0; k < K; k++) {
                if (gtmp < (G[u][k] + w[u][v][k] + R[v][k]) / c[k])
                    gtmp = (G[u][k] + w[u][v][k] + R[v][k]) / c[k];
                Gtmp[k] = G[u][k] + w[u][v][k];
                Rtmp[k] = R[v][k];
            }
            if (visited[v] == 0 && w[u][v][0] != Inf && Prefer_the_best(v, Ctmp, gtmp, Gtmp, Rtmp, c)) {
                hb->fibHeapInsert(v, Ctmp);
                C[v] = Ctmp;
                g[v] = gtmp;
                for (int k = 0; k < K ; k++)
                    G[v][k] = G[u][k] + w[u][v][k];
                pre_g[v] = u;
            }
        }
    }  
}

int H_MCOP(vector<vector<vector<eletype> > > w, vector<eletype> c, vector<eletype> &pre_r, vector<eletype> &pre_g, int n, int s, int t) {
    reserve_dij(w, c, pre_r, n, t);
    if (r[s] > K)
        return 0;
    look_ahead_dij(w, c, pre_g, n, s);
    int flag = 1;
    for (int k = 0; k < K; k++)
        flag &= (G[t][k] < c[k]);
    if (flag == 1) 
        return 1;
    return 0;
}

#endif //H_MCOP_H
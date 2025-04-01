#ifndef YUAN_H
#define YUAN_H

#include "heads.h"

struct path {
    vector<int> node; //路径节点
    vector<eletype> w; //路径权重和
};
vector<vector<path> > PATH;
vector<vector<vector<path> > > d;
vector<vector<eletype> > r;

void relax_g(int u, int v, vector<eletype> w) {
    for (int i2 = 0; i2 < X2; i2++)
        for (int i3 = 0; i3 < X3; i3++) {
            int j2, j3;
            for (j2 = X2 - 1; j2 >= 0; j2--)
                if (r[0][j2] < r[0][i2] - w[1]) break;
            for (j3 = X3 - 1; j3 >= 0; j3--)
                if (r[1][j3] < r[1][i3] - w[2]) break;
            if (j2 >= 0 && j3 >= 0) 
                if (d[v][i2][i3].w[0] > d[u][j2][j3].w[0] + w[0]) {
                    path p = d[u][j2][j3];
                    p.node.push_back(v);
                    p.w[0] += w[0];
                    d[v][i2][i3] = p;
                }
        }
}

int limited_granularity(vector<vector<vector<eletype> > > &w, vector<eletype> c, int n, int s, int t) {
    d.clear();
    d.resize(n);
    r.clear();
    r.resize(K - 1);
    for (int i = 0; i < K - 1; i++) {
        if (i == 0) {
            r[i].resize(X2);
            for (int i2 = 0; i2 < X2; i2++)
                r[i][i2] = c[1] / X2 * (i2 + 1);
        }
        if (i == 1) {
            r[i].resize(X3);
            for (int i3 = 0; i3 < X3; i3++)
                r[i][i3] = c[2] / X3 * (i3 + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        d[i].resize(X2);
        for (int i2 = 0; i2 < X2; i2++) {
            d[i][i2].resize(X3);
            for (int i3 = 0; i3 < X3; i3++) {
                d[i][i2][i3].w.resize(1);
                if (i == s) {
                    d[i][i2][i3].w[0] = 0;
                    d[i][i2][i3].node.push_back(s);
                }
                else
                    d[i][i2][i3].w[0] = Inf;
            }
        }
    }
    for (int i = 1; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                relax_g(u, v, w[u][v]);
    if (d[t][X2 - 1][X3 - 1].w[0] < c[0]) return 1;
    return 0;
}

void relax_p(int u, int v, vector<eletype> w) {
    for (int i = 0; i < PATH[u].size(); i++) {
        int flag_r = 1;
        for (int j = 0; j < PATH[v].size(); j++) {
            int flag = 1;
            for (int k = 0; k < K; k++)
                if (PATH[u][i].w[k] + w[k] < PATH[v][j].w[k])
                    flag = 0;
            if (flag) flag_r = 0;
            flag = 1;
            for (int k = 0; k < K; k++)
                if (PATH[u][i].w[k] + w[k] >= PATH[v][j].w[k])
                    flag = 0;
            if (flag) {
                PATH[v].erase(PATH[v].begin() + j);
                j--;
            }
        }
        if (flag_r && PATH[v].size() != X) {
            path p = PATH[u][i];
            p.node.push_back(v);
            for (int i = 0; i < K; i++)
                p.w[i] += w[i];
            PATH[v].push_back(p); 
        }
    }
}

int limited_path(vector<vector<vector<eletype> > > &w, vector<eletype> c, int n, int s, int t) {
    PATH.clear();
    PATH.resize(n);
    for (int i = 0; i < n; i++)
        PATH[i].clear();
    path p;
    p.node.push_back(s);
    p.w.resize(K, 0);
    PATH[s].push_back(p);
    for (int i = 1; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (u!=v) relax_p(u, v, w[u][v]);
    for (int i = 0; i < PATH[t].size(); i++) {
        int flag = 1;
        for (int j = 0; j < K; j++)
            if (PATH[t][i].w[j] > c[j])
                flag = 0;
        if (flag == 0)
            PATH[t].erase(PATH[t].begin() + i), i--;
    }
    if (PATH[t].size() != 0) return 1;
    return 0;
}

#endif //YUAN_H
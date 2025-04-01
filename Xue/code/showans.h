#ifndef ROUTER_SHOWANS_H
#define ROUTER_SHOWANS_H

#include "heads.h"
using namespace std;

vector<int> ans;
vector<vector<eletype> > w_ans(K, vector<eletype>(T, 0));

int showans(vector<int> pre, int s, int t) {
    printf("The Path from %d to %d is:\n", s, t);
    int i = 0;
    int cur = t;
    //依次输出路径上的节点
    ans.clear();
    while (cur != s) {
        ans.push_back(cur);
        cur = pre[cur];
    }
    ans.push_back(s);
    for (i = ans.size() - 1; i >= 0; i--)
        printf("%d ", ans[i]);
    printf("\n");
    return i; //可以返回路径上节点数
}

void calc(vector<vector<vector<eletype> > > &w, vector<int> pre, int s, int t, int total_num) {
    for (int i = 1; i < ans.size(); i++)
        for (int k = 0; k < K; k++)
            w_ans[k][total_num] += w[ans[i]][ans[i-1]][k];
}

int checkpath(vector<vector<vector<eletype> > > &w, vector<eletype> c) {
    vector<eletype> a;
    a.clear(); a.resize(3);
    for (int i = 1; i < ans.size(); i++)
        for (int k = 0; k < K; k++)
            a[k] += w[ans[i]][ans[i-1]][k];
    int flag = 1;
    for (int k = 0; k < K; k++)
        flag &= (a[k] < c[k]);
    return flag;
}

void extra_output() {
    eletype avg[3], md[3], pt90[3], m, m1, m2, p, p1, p2;
    m = (T - 1) * 0.5; m1 = floor(m); m2 = m - m1;
    p = (T - 1) * 0.9; p1 = floor(p); p2 = p - p1;
    for (int i = 0; i < K; i++)
        sort(w_ans[i].begin(), w_ans[i].end());
    for (int i = 0; i < K; i++) {
        if (i == 2)
            for (int j = 0; j < T; j++)
                w_ans[i][j] = (1 - exp(-w_ans[i][j])) * 100;
        avg[i] = 0;
        for (int j = 0; j < T; j++)
            avg[i] += w_ans[i][j];
        avg[i] /= T;
        md[i] = (1 - m2) * w_ans[i][m1 - 1] + m2 * w_ans[i][m1];
        pt90[i] = (1 - p2) * w_ans[i][p1 - 1] + p2 * w_ans[i][p1];
    }
    printf("\n");
    printf("Average of lat jit plr: %f %f %f\n", avg[0], avg[1], avg[2]);
    printf("Median of lat jit plr: %f %f %f\n", md[0], md[1], md[2]);
    printf("90th Percentile of lat jit plr: %f %f %f\n", pt90[0], pt90[1], pt90[2]);
}
#endif //ROUTER_SHOWANS_H

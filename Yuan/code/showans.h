#ifndef ROUTER_SHOWANS_H
#define ROUTER_SHOWANS_H

#include "heads.h"
using namespace std;

vector<int> ans;

int showans(path p, int s, int t) {
    printf("The Path from %d to %d is:\n", s, t);
    int i = 0;
    //依次输出路径上的节点
    ans.clear();
    for (i = 0; i < p.node.size(); i++)
        ans.push_back(p.node[i]);
    for (i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");
    return i; //可以返回路径上节点数
}

int checkpath(vector<vector<vector<eletype> > > &w, vector<eletype> c) {
    vector<eletype> a;
    a.clear(); a.resize(3);
    for (int i = 1; i < ans.size(); i++)
        for (int k = 0; k < K; k++)
            a[k] += w[ans[i-1]][ans[i]][k];
    int flag = 1;
    for (int k = 0; k < K; k++)
        flag &= (a[k] < c[k]);
    return flag;
}
#endif //ROUTER_SHOWANS_H

#ifndef ROUTER_GETGRAPH_H
#define ROUTER_GETGRAPH_H

#include "heads.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<vector<eletype> > lat(N), jit(N), plr(N);

// 生成符合高斯分布N(miu,sigma)的随机数
/*
eletype gaussrand(eletype miu, eletype sigma)
{
    eletype ans = -0.1;
    while(ans <= 0.0 || ans > 100.0) { //只取(0,100)的值
        double U, V;
        int phase = 0;
        eletype z;
        if (phase == 0) {
            U = rand() / (RAND_MAX + 1.0);
            V = rand() / (RAND_MAX + 1.0);
            z = sqrt(-2.0 * log(U)) * sin(2.0 * PI * V);
        } else
            z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
        phase = 1 - phase;
        ans = miu + z * sigma;
    }
    return ans;
}
*/

vector<vector<vector<eletype> > > getgraph(int dim){ //随机生成dim*dim的图，精度为小数点后两位，返回其邻接矩阵
    srand(time(0));
    vector<vector<vector<eletype> > > w(dim);
    for(int i = 0; i < dim; i++){
        w[i].resize(dim);
        lat[i].resize(dim);
        jit[i].resize(dim);
        plr[i].resize(dim);
        for(int j = 0; j < dim; j++){
            w[i][j].resize(K);
            if(i != j) { 
                lat[i][j] = (eletype)(rand() % 100000) / (eletype)100.0; //时延在0 - 1000 ms间均匀随机
                jit[i][j] = (eletype)(rand() % 10000) / (eletype)100.0; //抖动在0 - 100 ms间均匀随机
                plr[i][j] = (eletype)(rand() % 1000) / (eletype)100.0; //丢包率在0 - 10 %间均匀随机
                w[i][j][0] = lat[i][j];
                w[i][j][1] = jit[i][j];
                w[i][j][2] = -log(1 - plr[i][j] / 100);
            }
            else {
                lat[i][j] = -1;
                jit[i][j] = -1;
                plr[i][j] = -1;
                w[i][j][0] = 0;
                w[i][j][1] = 0;
                w[i][j][2] = 0;
            }
        }
    }
    return w;
}

void write(string file, vector<vector<eletype> > &matrix, int dim) { //把矩阵写入csv文件
    ofstream out(file);
    if (out.fail()) {
        cout << "File not open for output" << endl;
        return;
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim-1; j++)
            out << matrix[i][j] << ',';
        out << matrix[i][dim-1] << endl;
    }
    out.close();
    return;
}

void writegraph(int dim) {
    write("../../random_data/lat.csv", lat, dim);
    write("../../random_data/jit.csv", jit, dim);
    write("../../random_data/plr.csv", plr, dim);
    return;
}

#endif //ROUTER_GETGRAPH_H
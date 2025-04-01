#ifndef MAIN_CPP_READGRAPH_H
#define MAIN_CPP_READGRAPH_H

#include "heads.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//读csv文件的一行"line"，存到record中，以delimiter为分隔符
void file_to_string(vector<string> &record, string& line, char delimiter)
{
    int linepos = 0;
    char c;
    int linemax = line.length();
    string curstring;
    record.clear();
    while (linepos < linemax) {
        c = line[linepos];
        if (isdigit(c) || c == '.' || c == '-') {
            curstring += c;
        } else if (c == delimiter && curstring.size()) {
            record.push_back(curstring);
            curstring = "";
        }
        ++linepos;
    }
    if (curstring.size())
        record.push_back(curstring);
    return;
}
float string_to_float(string str) { //string转为float
    int flag, i, len = str.length();
    if (str[0] == '-') {
        flag = -1;
        i = 1;
    } else {
        flag = 1;
        i = 0;
    }
    float sum = 0;
    while (i < len) {
        if (str[i] == '.') break;
        sum = sum * 10 + str[i] - '0';
        ++i;
    }
    ++i;
    float t = 1, d = 1;
    while (i < len) {
        d *= 0.1;
        t = str[i] - '0';
        sum += t * d;
        ++i;
    }
    return flag * sum;
}
void read(string file, vector<vector<eletype> > &matrix) { //读csv文件，存入矩阵中
    vector<string> row;
    string line;
    ifstream in(file);
    if (in.fail()) {
        cout << "File not found" << endl;
        return;
    }
    int i = 0;
    while (getline(in, line) && in.good()) {
        file_to_string(row, line, ',');
        for (int j = 0, leng = row.size(); j < leng; j++) {
            matrix[i][j] = string_to_float(row[j]);
        }
        i++;
    }
    in.close();
    return;
}
vector<vector<vector<eletype> > > readgraph(int dim) {
    vector<vector<eletype> > lat(dim), jit(dim), plr(dim);
    for(int i = 0; i < dim; i++){
        lat[i].resize(dim);
        jit[i].resize(dim);
        plr[i].resize(dim);
    }
    //这里的三个读文件的函数返回的是一个dim*dim的矩阵，元素为对应值。其中异常项（无穷或0）读出为-1.0
    //读取的文件是在原始数据的基础上，使用Python中pandas处理得到的
    //另外，方便起见，我们在程序中把节点编号改为使用从0到12的整数来处理
    //其顺序为[3002,3005,3006,3007,3008,9001,9002,9003,9004,9005,9006,9105,9106]
    read("../../data/lat2.csv", lat);
    read("../../data/jit2.csv", jit);
    read("../../data/plr2.csv", plr);
    vector<vector<vector<eletype> > > w(dim);
    for (int i = 0; i < dim; i++) {
        w[i].resize(dim);
        for (int j = 0; j < dim; j++) {
            w[i][j].resize(K);
            if (lat[i][j] < 0.0 && i != j) {
                w[i][j][0] = Inf;
                w[i][j][1] = Inf;
                w[i][j][2] = Inf;
            }
            else if(i != j) {
                w[i][j][0] = lat[i][j];
                w[i][j][1] = jit[i][j];
                w[i][j][2] = -log(1-plr[i][j]/100);
            }
            else {
                w[i][j][0] = 0;
                w[i][j][1] = 0;
                w[i][j][2] = 0;
            }
        }
    }
    return w;
}
vector<vector<vector<eletype> > > readgraph2(int dim) {
    vector<vector<eletype> > lat(dim), jit(dim), plr(dim);
    for(int i = 0; i < dim; i++){
        lat[i].resize(dim);
        jit[i].resize(dim);
        plr[i].resize(dim);
    }
    //这里的三个读文件的函数返回的是一个dim*dim的矩阵，元素为对应值。其中异常项（无穷或0）读出为-1.0
    //读取的文件是在原始数据的基础上，使用Python中pandas处理得到的
    //另外，方便起见，我们在程序中把节点编号改为使用从0到12的整数来处理
    //其顺序为[3002,3005,3006,3007,3008,9001,9002,9003,9004,9005,9006,9105,9106]
    read("../../random_data/lat.csv", lat);
    read("../../random_data/jit.csv", jit);
    read("../../random_data/plr.csv", plr);
    vector<vector<vector<eletype> > > w(dim);
    for (int i = 0; i < dim; i++) {
        w[i].resize(dim);
        for (int j = 0; j < dim; j++) {
            w[i][j].resize(K);
            if (lat[i][j] < 0.0 && i != j) {
                w[i][j][0] = Inf;
                w[i][j][1] = Inf;
                w[i][j][2] = Inf;
            }
            else if(i != j) {
                w[i][j][0] = lat[i][j];
                w[i][j][1] = jit[i][j];
                w[i][j][2] = -log(1-plr[i][j]/100);
            }
            else {
                w[i][j][0] = 0;
                w[i][j][1] = 0;
                w[i][j][2] = 0;
            }
        }
    }
    return w;
}
#endif //MAIN_CPP_READGRAPH_H

#include "heads.h"
#include "readgraph.h"
#include "getgraph.h"
#include "H_MCOP.h"
#include "showans.h"

int main() {
    freopen("1.txt","w",stdout); //运行结果重定向到1.txt中

    eletype D = 500, J = 50, L = 10;
    vector<vector<vector<eletype> > > w;
    vector<eletype> pre_r,pre_g;
    vector<eletype> c{D, J, -log(1 - L / 100)};
    double total_time = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, n;

    int cond = 2; //选择情况1或2
    if (cond == 1) {
        n = N;
        w = getgraph(n);  //随机生成图
        // w = readgraph2(n);  //从random_data中得到图
        writegraph(n); //把图输出到文件夹random_data中
    }
    else if (cond == 2) {
        n = Dim;
        w = readgraph(n);  //从data中得到图
    }
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j) {
                clock_t startTime,endTime;
                startTime = clock(); //计时开始

                pre_r.clear(); pre_g.clear();
                pre_r.resize(n); pre_g.resize(n);
                printf("%d %d:\n",i,j);
                int ret = H_MCOP(w, c, pre_r ,pre_g, n, i, j);
                if (ret == 1) {
                    cnt1++;
                    showans(pre_g, i, j);
                    if (checkpath(w, c)) cnt2++;
                }
                else {
                    cnt3++;
                    printf("there is no feasible path\n");
                }

                endTime = clock(); //计时结束
                printf("The run time is: %lf s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
                total_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n");
            }
    printf("The total run time is: %lf s\n", total_time);
    printf("The average run time is: %lf s\n", total_time / (n * (n-1)));
    printf("total pairs: %d\n", n * (n-1));
    printf("found paths: %d\n", cnt1);
    printf("feasible paths: %d\n", cnt2);
    printf("not found paths: %d\n", cnt3);
    return 0;
}
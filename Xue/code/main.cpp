#include "heads.h"
#include "readgraph.h"
#include "getgraph.h"
#include "Xue.h"
#include "showans.h"

int main() {
    freopen("1.txt","w",stdout); //运行结果重定向到1.txt中

    eletype D = 500, J = 50, L = 10;
    vector<vector<vector<eletype> > > w;
    vector<eletype> c{D, J, -log(1 - L / 100)};
    double total_time = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, n;

    int cond = 1; //选择情况1或2
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
    int flag = 1; // flag=1时使用额外输出模式
    int total_num = 0, end = 0;
    
    pre_compute(w, c, n);
    for (int i = 0; i < n && !end; i++)
        for (int j = 0; j < n; j++)
            if (i != j) {
                if (flag && total_num == T) {
                    end = 1;
                    break;
                }
                clock_t startTime,endTime;
                startTime = clock(); //计时开始

                printf("%d %d:\n", i, j);
                int ret;
                ret = dij_heap(w_M, n, i, j);
                if (ret == 1) {
                    cnt1++;
                    int num;
                    showans(pre, i, j);
                    if (flag) calc(w, pre, i, j, total_num);
                    if (checkpath(w, c)) cnt2++;
                }
                else {
                    cnt3++;
                    printf("there is no feasible path\n");
                }
                total_num++;

                endTime = clock(); //计时结束
                printf("The run time is: %lf s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
                total_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n");
            }

    printf("The total run time is: %lf s\n", total_time);
    printf("The average run time is: %lf s\n", total_time / total_num);
    printf("total pairs: %d\n", total_num);
    printf("found paths: %d\n", cnt1);
    printf("feasible paths: %d\n", cnt2);
    printf("not found paths: %d\n", cnt3);
    if (flag) extra_output();
    return 0;
}
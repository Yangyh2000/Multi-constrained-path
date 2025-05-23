# Xue算法实验报告

无98 杨元昊 2019011197

1. “算法运行示例”截图

   情况一：图100个节点。三种属性随机生成。

   输出包括：每对节点之间选出的路径经过的节点，每对节点之间计算过程的计算时间，以及总计算时间和平均计算时间。同时把随机生成的100个节点的三个属性输出到文件夹random_data里。

   情况二：图13个节点。三种属性从data文件夹中读取。

   输出包括：每对节点之间选出的路径经过的节点，每对节点之间计算过程的计算时间，以及总计算时间和平均计算时间。

   下面的截图为情况二的运行结果截图。（情况一只需把`int cond = 2;`改为`int cond = 1;`）

   ![image-20220418144917682](C:\Users\11147\AppData\Roaming\Typora\typora-user-images\image-20220418144917682.png)

2. 变量说明

   函数参数：

   在函数`pre_compute(w, c, n)`中，w表示链路的加性权重$w_k(u,v)$，c表示权重的约束$c_k$，n表示节点的个数。

   在函数`dij_heap(w, n, s, t)`中，u，w表示每个边的辅助边的权重$w_M(u,v)$，n表示节点的个数，s表示源点，t表示汇点。

   全局变量：

   在`Xue.h`中，pre表示最短路径上节点的前驱节点，w_M表示辅助边的权重。

   在`getgraph.h`中，lat，jit，plr分别表示往返时延，时延抖动，丢包率。

   在`showans.h`中，ans表示输出的路径，w_ans表示额外输出模式下计算路径时延、抖动、丢包等参数。

   在`heads.h`中，N表示情况一的节点数100，Dim表示情况二的节点数13，K表示约束的个数3，Inf表示设定一个足够大的数1e6即$10^6$，T表示额外输出模式下计算的节点对个数。

3. 算法运行时间的统计结果

   设定时延、抖动和丢包率的上限分别为500 ms，50 ms，10 %。

   情况一中随机的数据精度为小数点后两位，时延在0 - 1000 ms间均匀随机，抖动在0 - 100 ms间均匀随机，丢包率在0 - 10 %间均匀随机。

   情况一：一共计算100 * 99 个有序节点对，总计算时间为2.640036 s，平均每对计算时间为0.000267 s。

   情况二：一共计算13 * 12个有序节点对，总计算时间为0.002936 s，平均每对计算时间为0.000019 s。

   
# 计网HW2

## P1

![image-20230922154909662](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922154909662.png)

1. 错
2. 对
3. 错
4. 错
5. 错

## P3

![image-20230922154934695](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922154934695.png)

- 应用层：DNS
- 运输层：UDP、TCP

## P7

![image-20230922154957897](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922154957897.png)

$T=2RRT_0+RTT_1+RTT_2+...+RTT_n$



## P8

![image-20230922155026072](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922155026072.png)

a.没有并行TCP连接的非持续HTTP

b.配置有五个并行连接的非持续HTTP

c.持续HTTP



P7中时间设为T

1. $T+8\times2RTT_0=18RTT_0+RTT_1+RTT_2+...+RTT_n$

2. $T+2\times2RTT_0=6RTT_0+RTT_1+RTT_2+...+RTT_n$

3. 流水线：$T+RTT_0=3RTT_0+RTT_1+RTT_2+...+RTT_n$

   没有流水线：$T+8RTT_0=10RTT_0+RTT_1+RTT_2+...+RTT_n$

   

## P9

![image-20230922155201906](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922155201906.png)

<img src="C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230922165015016.png" alt="image-20230922165015016" style="zoom: 50%;" />

1. $\Delta=\frac{850000bits}{15Mbps}$

    平均接入时延$\frac{\Delta}{(1-\Delta\beta)}\approx0.6s$

    总的平均响应时间$0.6+3=3.6s$

   

2. 未命中平均接入时延$\frac{Delta}{(1-p\Delta\beta)}\approx0.089s$

   未命中总的平均响应时间$0.089+3=3.089s$

   命中则认为时延几乎为0

   平均响应时间为$0.4\times3.089s\approx1.24s$


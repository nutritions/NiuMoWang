<h1 align = "center">计组week1</h1>



## 题目一

真值表：

|  A   |  B   | $\overline{A+B}$ | $\overline{A}·\overline{B}$ |
| :--: | :--: | :--------------: | :-------------------------: |
|  0   |  0   |        1         |              1              |
|  0   |  1   |        0         |              0              |
|  1   |  0   |        0         |              0              |
|  1   |  1   |        0         |              0              |



|  A   |  B   | $\overline{A·B}$ | $\overline{A}+\overline{B}$ |
| :--: | :--: | :--------------: | :-------------------------: |
|  0   |  0   |        1         |              1              |
|  0   |  1   |        1         |              1              |
|  1   |  0   |        1         |              1              |
|  1   |  1   |        0         |              0              |



两个真值表左右结果一样，说明上面两个公式成立



搭建二输入异或门：

![image-20230315160935513](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230315160935513.png)

## 题目二

转成十进制：

$(101001)_2=41$

$(52)_8=42$

$(00101001)_{BCD}=29$

$(33)_{16}=51$



所以：$(00101001)_{BCD}<(101001)_2<(52)_8<(33)_{16}$



## 题目三

### (1)

- ALU（算术逻辑单元）：是一种用于执行算术和逻辑操作的电路组件。在计算机的 CPU 中，ALU 执行诸如加法、减法、逻辑 AND、OR、NOT 等操作，它的输出结果可以被送到寄存器、内存或其他电路中
- REG FILE（寄存器文件）：是一组用于存储 CPU 内部操作的数据存储单元。在 LC-3 中，寄存器文件包含 8 个 16 位寄存器，其中 7 个用于存储数据，另一个用于存储程序计数器。在执行指令时，寄存器文件用于存储指令的操作数和结果
- MUX（多路复用器）：是一种电路组件，用于选择并输出一个或多个输入信号中的一个。在 LC-3 中，MUX 通常用于从多个输入信号中选择一个
- MEMORY（内存）：指存储器，用于存储程序指令和数据。它是计算机系统中非常重要的组成部分，因为所有的程序和数据都必须存储在存储器中才能被CPU处理





### (2)

cpu对应了ALU和MUX和REG FILE

内存对应了MEMORY



### (3)

输入设备：键盘、鼠标

输出设备：显示器、打印机









## 题目四

```verilog
module Reg (
input clk,
input reset,
input [7:0] d,
output reg [7:0] q
);

always @(negedge clk) begin
    if (reset) begin
        q <= 8'h12;
    end else begin
        q <= d;
    end
end

endmodule

```

异步复位：

```verilog
module Reg (
input clk,
input reset,
input [7:0] d,
output reg [7:0] q
);

always @(negedge clk) begin
    if (reset) begin
        q <= 8'h12;
    end else begin
        q <= d;
    end
end

// 异步复位
always @(posedge reset) begin
    if (reset) begin
        q <= 8'h12;
    end
end

endmodule

```



## 实验题1

![image-20230309094851766](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20230309094851766.png)





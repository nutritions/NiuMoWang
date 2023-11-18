#  <h1 align = "center">HW6</h1>

## T1

```assembly
SaveRegisters    	ST  R0,SAVER0
               ST  R3,SAVER3
               ST  R4,SAVER4
               ST  R5,SAVER5
               ST  R6,SAVER6
```

```assembly
RestoreRegisters	 ST  R0,SAVER0
               ST  R3,SAVER3
               ST  R4,SAVER4
               ST  R5,SAVER5
               ST  R6,SAVER6
```

```assembly
SAVERO		.FILL  X0000
SAVER3		.FILL  X0000
SAVER4		.FILL  X0000
SAVER5		.FILL  X0000
SAVER6		.FILL  X0000
```



## T2

```assembly
CLEAR	LEA R3,MASKS
	   LDR R3,R3,R1
	   NOT R3,R3
	   AND R0,R0,R3
```



```assembly
SET		LEA R3,MASKS
	   LDR R3,R3,R1
	   NOT R3,R3
	   NOT R0,R0
	   AND R0,R0,R3
	   NOT RO,RO
```



## T3

a. 除去伪操作，共16bits

b. x400F

c. 内存中四个值的和再右移两位，即平均值

## T4

第四行：改为BRnz

## T5

a. KBSR[15]若是0，则可能会重复读取相同数据

b. KBSR[15]若为1，则KBDR数据没有读取，不进行检查可能导致丢失

c. 第一种，因为处理器读取速度远快于键入速度

## T6

## T7

a.256

b.3

## T8

output is "FUN"

## T9

result为1：A是质数

result为0：A不是质数

## T10

> ADD R1, R1, #1
>
> TRAP x25
>
> ADD R0, R0, #5
>
> BRzp K



## T11

a.重复输出“2”

b.在屏幕上将输入字符显示两次

c. 

d.

## T12

1.堆栈不平衡




# 编译原理HW2

## 3.1a

![image-20231007125250452](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125250452.png)

![image-20231007130305149](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007130305149.png)

## 3.2a

![image-20231007125300972](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125300972.png)

$S\rightarrow aSbS \rightarrow a\varepsilon bS \rightarrow a\varepsilon baSbS \rightarrow a\varepsilon ba\varepsilon bS\rightarrow a\varepsilon ba\varepsilon b\varepsilon \rightarrow abab$

$S\rightarrow abSaSbS\rightarrow ab\varepsilon aSbS\rightarrow ab\varepsilon a\varepsilon bS\rightarrow ab\varepsilon a\varepsilon b\varepsilon\rightarrow abab$



## 3.10

![image-20231007125236761](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125236761.png)

- First集

First(TL)={int, real}

First(int)={int}

First(real)={real}

First(id R)={id}

First(,id R)={,}

First($\varepsilon$)={$\varepsilon$}

- Follow集

Follow(D)={$}

Follow(T)={id}

Follow(L)={$}

Follow(R)={$}

- SELECT集

SELECT{$D\rightarrow TL$}={int,real}

SELECT{$T\rightarrow int$}={int}

SELECT{$T\rightarrow real$}={real}

SELECT{$L\rightarrow id R$}={id}

SELECT{$R\rightarrow ,id R$}={,}

SELECT{$R\rightarrow \varepsilon$}={$}

分析表：

|      | int                |        real        |         id          |          ,           |             $              |
| ---- | ------------------ | :----------------: | :-----------------: | :------------------: | :------------------------: |
| D    | $D\rightarrow TL$  | $D\rightarrow TL$  |                     |                      |                            |
| T    | $T\rightarrow int$ | $T\rightarrow int$ |                     |                      |                            |
| L    |                    |                    | $L\rightarrow id R$ |                      |                            |
| R    |                    |                    |                     | $R\rightarrow ,id R$ | $R\rightarrow \varepsilon$ |



## 3.11

![image-20231007125152882](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125152882.png)



- First集

First(aBS)={a}

First(bAS)={b}

First(bAA)={b}

First(aBB)={a}

First(a)={a}

First(b)={b}

First($\varepsilon$)={$\varepsilon$}

- Follow集

Follow(S)={$}

Follow(A)={a,b,$}

Follow(B)={a,b,$}

- SELECT集

SELECT{$S\rightarrow aBS$}={a}

SELECT{$S\rightarrow bAS$}={b}

SELECT{$S\rightarrow \varepsilon$}={$}

SELECT{$A\rightarrow bAA$}={b}

SELECT{$A\rightarrow a$}={a}

SELECT{$B\rightarrow aBB$}={a}

SELECT{$B\rightarrow b$}={b}

分析表：

|      | a                  | b                  | $                          |
| ---- | ------------------ | ------------------ | -------------------------- |
| S    | $S\rightarrow aBS$ | $S\rightarrow bAS$ | $S\rightarrow \varepsilon$ |
| A    | $A\rightarrow a$   | $A\rightarrow bAA$ |                            |
| B    | $B\rightarrow aBB$ | $B\rightarrow b$   |                            |



## 3.17

![image-20231007125341308](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125341308.png)

拓展文法：

S'->S 

S->(L) | a 

L->L, S | S

![image-20231007132725895](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007132725895.png)



## 3.19a

![image-20231007125401964](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007125401964.png)

拓展文法：

E'->E

E->E+T 

E-> T 

T->TF 

T->F 

F->F* 

F->a 

F->b 

状态如下：

![image-20231007133743883](C:\Users\Nutrition\AppData\Roaming\Typora\typora-user-images\image-20231007133743883.png)

|      | +    | *    | a    | b    | $    | E    | T    | F    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 0    |      |      | s4   | s5   |      | 1    | 2    | 3    |
| 1    | s6   |      |      |      | acc  |      |      |      |
| 2    | r2   |      | s4   | s5   | r2   |      |      | 7    |
| 3    | r4   | s8   | r4   | r4   | r4   |      |      |      |
| 4    | r6   | r6   | r6   | r6   | r6   |      |      |      |
| 5    | r7   | r7   | r7   | r7   | r7   |      |      |      |
| 6    |      |      |      | s4   | s5   |      | 9    | 3    |
| 7    | r3   | s8   | r3   | r3   | r3   |      |      |      |
| 8    | r5   | r5   | r5   | r5   | r5   |      |      |      |
| 9    | r1   |      | s4   | s5   | r1   |      |      | 7    |


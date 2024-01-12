
	.ORIG	x3000	;程序从x3000开始
	LDI	R1, P		;载入p到R1
	LDI	R2, Q		;载入q到R2
	LDI	R3, N		;载入N到R3
	ADD	R3, R3, #-2	;循环次数为N-2
	AND	R0, R0, #0	;R0清零，用于储存F（N）
	AND	R4, R4, #0	;R4清零，用于储存F（N-2）
	AND	R5, R5, #0	;R5清零，用于储存F（N-1）
	AND	R6, R6, #0	;R6清零用于储存模p后结果
	AND	R7, R7, #0	;R7清零用于储存模p后结果
	ADD	R4, R4, #1	;F（0）等于1
	ADD	R5, R5, #1	;F（1）等于1
;模p				;计算R6=R4%R1
AGAIN	ADD	R0, R1, #0
L2	ADD	R6, R0, #0
	NOT	R6, R6
	ADD	R6, R6, #1
	ADD	R6, R4, R6	;以上计算被模数与按倍数增长后的模的差值,利用R6作转接保持R0不变
	BRn	L1		    ;若差值为负数，跳转到L1
	ADD	R0, R0, R1	;若为正数，则继续增加倍数
	BRnzp	L2		;跳转到L2，继续计算差值并判断
L1	ADD	R6, R1, #0	
	NOT	R6, R6
	ADD	R6, R6, #1
	ADD	R0, R0, R6
	NOT	R0, R0
	ADD	R0, R0, #1
	ADD	R6, R4, R0	;差值为负数，则将倍数增长后的值减去一次模，再由被模数减去即可得到余数
;模q				;计算R7=R5%R2
	ADD	R0, R2, #0	;计算方法同模p
L4	ADD	R7, R0, #0
	NOT	R7, R7
	ADD	R7, R7, #1
	ADD	R7, R5, R7
	BRn	L3
	ADD	R0, R0, R2
	BRnzp	L4
L3	ADD	R7, R2, #0
	NOT	R7, R7
	ADD	R7, R7, #1
	ADD	R0, R0, R7
	NOT	R0, R0
	ADD	R0, R0, #1
	ADD	R7, R5, R0
;更新函数各项		;每计算一次F（N-1）和F（N-2），更新一次，便于下次循环的计算
	ADD	R0, R6, R7	;得到当前循环的F（N）
	ADD	R4, R5, #0	;将F（N-1）赋给F（N-2）
	ADD	R5, R0, #0	;将F（N）赋给F(N-1)
;判断循环是否进行
	ADD	R3, R3, #0	;读出R3便于判断
	BRz	FINISH		;判断是否循环是否进行了N-2次，若已完成则跳转到FINISH
	ADD	R3, R3, #-1	;没有进行N-2次则将R3的值递减
	BRnzp	AGAIN		;无条件跳转至AGAIN处进行下一次循环
FINISH	STI	R0, ANS		;将R0中储存的F（N）的值存到x3103中
	HALT			;程序结束
P	.FILL	x3100
Q	.FILL	x3101
N	.FILL	x3102
ANS	.FILL	x3103
	.END
; 采用冒泡排序，将成绩排好序后，转移到指定地址中，再进行等级的计数
	    .ORIG	x3000 		               
; 排序部分:
; i（R3 0~len-1）
; j (R4 0~len-1-i)
LABEL1  AND     R4, R4, #0                  ;j=0
        LD      R0, BEFORE                  
LABEL2	LDR	    R5, R0, #0		            ;R5：BEFORE[j]
		LDR	    R6, R0, #1		            ;R6：BEFORE[j+1]
		NOT	    R7, R5	
		ADD	    R7, R7, #1	
		ADD	    R7, R6, R7	                ;BEFORE[j+1]-BEFORE[j]
		BRn     LABEL4		                ;不满足升序，则跳到交换

LABEL3  ADD	    R4, R4, #1                  ;j++
        ADD	    R0, R0, #1		            		                
		ADD	    R6, R4, R3  
		ADD     R6, R6, #-15                ;j<（len-1-i）?
		BRn	    LABEL2                      ;小于则继续比较j++后的相邻两位
		BRnzp   LABEL5                      ;否则j循环完成一轮，i循环+1
		
LABEL4  ADD     R7, R6, #0                  ;swap
        ADD     R6, R5, #0
        ADD     R5, R7, #0
		STR	    R5, R0, #0 
		STR	    R6, R0, #1
		BRnzp   LABEL3                      ;无论是否交换都判断j循环是否完成

LABEL5	ADD	    R3, R3, #1	                ;i++
	    ADD	    R6, R3, #-15                ;i<（len-1）?
	    BRn	    LABEL1		                ;小于则继续i循环

;结果转移部分：
    	LD	    R0, BEFORE	                
	    LD	    R1, AFTER		            
	    LD	    R2, NUM	
AGAIN   LDR		R7, R0, #0		            
	    STR		R7, R1, #0		            ;R0指针地址存储数据转移到R1指针地址存储
	    ADD		R0, R0, #1		            
	    ADD		R1, R1, #1		            
	    ADD		R2, R2, #-1	                
	    BRp		AGAIN		                ;循环转移
 
;统计部分：
; A等级人数（最多前4）
; B等级人数（最多前8）
	    AND	    R5, R5, #0		            ;R5：A等级
	    AND	    R6, R6, #0		            ;R6：B等级
	    LD	    R1, AFTER
	    LD	    R2, NUM	
NEXT    ADD     R1, R1, #1
        ADD     R0, R2, #-8
        BRz     FINISH
        LDR	    R7, R1, #7	
        ADD     R2, R2, #-1
        ADD     R7, R7, #-15
        ADD     R7, R7, #-15
        ADD     R7, R7, #-15
        ADD     R7, R7, #-15
        ADD     R7, R7, #-15
        ADD     R7, R7, #-10                
        BRn     L1                          ;判断是否大于等于85，小于则跳L1继续与75比较
        ADD     R0, R2, #-12                
        BRn     L2                          ;判断是否在前4
        ADD     R6, R6, #1                  ;否则B等级，是则跳L2是A等级
        BRnzp   NEXT
L1	    ADD     R7, R7, #10
	    BRn     NEXT                        ;L1基础上大于等于75则B等级
	    ADD     R6, R6, #1
	    BRnzp   NEXT
L2      ADD     R5, R5, #1
        BRnzp   NEXT


; 储存结果部分：
FINISH	STI	    R5, ansA
    	STI	    R6, ansB
	    HALT			                    
BEFORE	        .FILL	x4000		               
AFTER	        .FILL	x5000		
NUM	            .FILL	#16	
ansA	        .FILL	x5100		
ansB	        .FILL	x5101

	   .END			
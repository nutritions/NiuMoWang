        ;R0读入N，R1指针，R2最大长度，R3当前长度
        ;R4当前字符，R5上一位字符，R6和R7作tmp
        .ORIG   x3000
        AND     R0, R0, #0;
        AND     R1, R1, #0;
        AND     R2, R2, #0;
        AND     R3, R3, #0;
        AND     R4, R4, #0;
        AND     R5, R5, #0;
        AND     R6, R6, #0;
        AND     R7, R7, #0;初始化
        LDI     R0, NUM;
        LD      R1, DATA;
        LDR     R4, R1, #0;
        ADD     R2, R2, #1;
LABEL2  AND     R3, R3, #0;当前与上一位不同，当前长度重新计数
LABEL1  ADD     R3, R3, #1;当前长度加1
        ADD     R0, R0, #-1;
        BRz     FINISH;全部读入则跳转
        
        ADD     R5, R4, #0;
        ADD,    R1, R1, #1;
        LDR     R4, R1, #0;更新当前位和上一位

;判断前一位和当前位是否相同
        ADD     R6, R4, #0;
        NOT     R6, R6;
        ADD     R6, R6, #1;
        ADD     R7, R5, R6;得到R7=R5-R4
        BRz     LABEL1;相同则跳转LABEl1，不同则比较当前长度和最大长度
        
;比较当前长度和最大长度        
        ADD     R6, R2, #0;
        NOT     R6, R6;
        ADD     R6, R6, #1;
        ADD     R7, R3, R6;得到R7=R3-R2
        BRn     LABEL2;
        ADD     R2, R3, #0;
        BRnzp   LABEL2;当前更长则更新最大长度，两种情况都跳转LABEL2

;最后出现的字符是最长的情况在此作判断        
FINISH  ADD     R6, R2, #0;
        NOT     R6, R6;
        ADD     R6, R6, #1;
        ADD     R7, R3, R6;
        BRn     STORE;
        ADD     R2, R3, #0;
STORE   STI     R2, RESULT;
        HALT
        
RESULT  .FILL   x3050
NUM     .FILL   x3100
DATA    .FILL   x3101

        .END
        
        
.data
save: .word 0x0001,0x0001
kbsr: .word 0x7f00
kbdr: .word 0x7f04
.text
addi t2,zero,1
addi t3,zero,32					#空格作为终止符
addi x11,zero,2					#计数，判断是否两位数
cal:
beq x11,zero,doubdigit				#一位数
addi t5,t4,-48
jal zero start
doubdigit:					#两位数
addi t6,t4,-48
slli x12,t5,3
add x12,x12,t5
add t5,x12,t5
add t5,t5,t6
start:
lw t1, kbsr
lw t1, 0(t1)
bne t1,t2,start					#判断kbsr
lw t4, kbdr
lw t4, 0(t4)
addi x11,x11,-1
bne t4, t3,cal					#判断是否为终止符
      
# 将n加载到寄存器t0中

add t0, t5,zero

la a0, save
# 将第一项和第二项加载到寄存器t1和t2中
lw t1, 0(a0)
lw t2, 4(a0)
# 将第一项保存到内存中
sw t1, 0(a0)
# 将第二项保存到内存中
sw t2, 4(a0)
# 初始化计数器i为2
li t3, 2
loop:
  # 如果i >= n，跳出循环
  bge t3, t0, end
  # 计算下一项的值
  add t4, t1, t2
  # 保存下一项的值到内存中
  slli t5, t3, 2				#4*i
  add t5, t5, a0
  sw t4, 0(t5)
  # 更新t1和t2
  add t1, zero, t2
  add t2, zero, t4
  # 更新计数器i
  addi t3, t3, 1
  # 继续循环
  jal zero loop
end:

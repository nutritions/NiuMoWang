.data
save: .word 0x0001,0x0001

.text 
# 将n加载到寄存器t0中
addi t0,zero,40

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
  # 如果i = n，跳出循环
  beq t3, t0, end
  # 计算下一项的值
  add t4, t1, t2
  # 保存下一项的值到内存中
  add t5, t3, t3
  add t5, t5, t3
  add t5, t5, t3			#4*i
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

.data
save: .word 0x0001,0x0001
kbsr: .word 0x7f00
kbdr: .word 0x7f04
.text
addi t2,zero,1
addi t3,zero,32					#�ո���Ϊ��ֹ��
addi x11,zero,2					#�������ж��Ƿ���λ��
cal:
beq x11,zero,doubdigit				#һλ��
addi t5,t4,-48
jal zero start
doubdigit:					#��λ��
addi t6,t4,-48
slli x12,t5,3
add x12,x12,t5
add t5,x12,t5
add t5,t5,t6
start:
lw t1, kbsr
lw t1, 0(t1)
bne t1,t2,start					#�ж�kbsr
lw t4, kbdr
lw t4, 0(t4)
addi x11,x11,-1
bne t4, t3,cal					#�ж��Ƿ�Ϊ��ֹ��
      
# ��n���ص��Ĵ���t0��

add t0, t5,zero

la a0, save
# ����һ��͵ڶ�����ص��Ĵ���t1��t2��
lw t1, 0(a0)
lw t2, 4(a0)
# ����һ��浽�ڴ���
sw t1, 0(a0)
# ���ڶ���浽�ڴ���
sw t2, 4(a0)
# ��ʼ��������iΪ2
li t3, 2
loop:
  # ���i >= n������ѭ��
  bge t3, t0, end
  # ������һ���ֵ
  add t4, t1, t2
  # ������һ���ֵ���ڴ���
  slli t5, t3, 2				#4*i
  add t5, t5, a0
  sw t4, 0(t5)
  # ����t1��t2
  add t1, zero, t2
  add t2, zero, t4
  # ���¼�����i
  addi t3, t3, 1
  # ����ѭ��
  jal zero loop
end:

.data
save: .word 0x0001,0x0001

.text 
# ��n���ص��Ĵ���t0��
addi t0,zero,40

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
  # ���i = n������ѭ��
  beq t3, t0, end
  # ������һ���ֵ
  add t4, t1, t2
  # ������һ���ֵ���ڴ���
  add t5, t3, t3
  add t5, t5, t3
  add t5, t5, t3			#4*i
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

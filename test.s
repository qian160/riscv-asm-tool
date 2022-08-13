.global _start
.section .text
_start:
  li x1,0x11      #addi x1,x0,0x11
  sb x1,0(x0)
  lb x2,0(x0)
  mv x3,x2        #read after load
  bge x2,x1,target
  li x3,0x33      #should not be execuated
  li x4,0x44
target:
  beqz x0,target
  nop
  nop
  nop

.org 0x200
bad:
  li x1,0
  li x2,0

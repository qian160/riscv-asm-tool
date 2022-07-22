_start:
  li x1,0x11
  li x2,0x22
  bge x2,x1,target
  li x3,0x33
  li x4,0x44
target:
  nop
  nop
  nop
  nop

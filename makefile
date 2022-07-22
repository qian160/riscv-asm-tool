run:
  riscv64-linux-gnu-as test.s -o test.o
  riscv64-linux-gnu-objdump -d test.o > asm.txt
  ./as
  @echo
  @echo success!
  #./as > some_file_name   #redirect the output
  @rm asm.txt
  @rm test.o

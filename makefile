INST_ROM = ../Inst_Rom.data
generate:  
	@riscv64-linux-gnu-as test.s -o test.o
	@riscv64-linux-gnu-objdump -d test.o  > asm.txt
	#@riscv64-linux-gnu-objdump -d -M no-aliases test.o  > asm-original.txt
	@echo 
print:generate
	@./as
	@rm test.o

update:generate
	@./as > $(INST_ROM)
	@rm test.o

clean:
	rm asm.txt

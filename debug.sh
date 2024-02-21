rm blend.o;
rm mulBlendDebug;
nasm -f elf -F stabs xmmBlend.s -o blend.o;
ld -m elf_i386 blend.o -o mulBlendDebug.o;

ddd mulBlendDebug.o;
rm tp;
nasm -f elf32 helloworld.s -o helloworld.o;
nasm -f elf32 multiplyBlend.s -o multiplyBlend.o;
nasm -f elf32 xmmBlend.s -o xmmBlend.o;
gcc -m32 main.c lectorBmp.c filtros.c helloworld.o multiplyBlend.o xmmBlend.o -o tp;
./tp;

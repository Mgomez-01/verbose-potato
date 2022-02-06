all: testBitwiseFunctions testFramework gameboy

gameboy: assignment1.c
	clang -g -c -Wall -o assignment1.o assignment1.c
	clang simpledisplay.o color.o cpu.o app.o assignment1.o -L. -lphobos2 -lpthread -ldl -o gameboy

testFramework: assignment1.c
	clang -g -c -Wall -o assignment1.o assignment1.c
	clang testframework.o cpu.o assignment1.o -L. -lphobos2 -lpthread -o testFramework

testBitwiseFunctions: testBitwiseFunctions.c assignment1.c
	clang -o testBitwiseFunctions -g -Wall testBitwiseFunctions.c assignment1.c

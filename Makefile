.phony all:
all: ssi

ssi: main.c
	gcc main.c bg_pro.c util.c -o ssi

.PHONY clean:
clean:
	-rm -rf *.o *.exe
	
pack:
	tar zcvf p1.tar.gz main.c bg_pro.c bg_pro.h util.c util.h Makefile

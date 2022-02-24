CC=gcc
OPT=-Wall -lm
EXEC=OScratch
TARGET=	couche_1.o\
		couche_2.o\
		couche_3.o\
		couche_4.c

all : $(EXEC)

#compile couche_1
couche_1.o : couche_1.c
	$(CC) -o couche_1.o -c couche_1.c $(OPT)

#compile couche_2
couche_2.o : couche_2.c
	$(CC) -o couche_2.o -c couche_2.c $(OPT)

#compile couche_3
couche_3.o : couche_3.c
	$(CC) -o couche_3.o -c couche_3.c $(OPT)

#compile couche_3
couche_4.o : couche_4.c
	$(CC) -o couche_4.o -c couche_4.c $(OPT)

#compile main
main.o : main.c
	$(CC) -o main.o -c main.c $(OPT)

#compile test
test.o : test.c
	$(CC) -o test.o -c test.c $(OPT)

#compile cmd_dump_inodes
# cmd_dump_inodes : cmd_dump_inodes.c
# 	$(CC) cmd_dump_inodes.c -o cmd_dump_inodes $(OPT)

#link main avec liste et element
$(EXEC): $(TARGET) main.o
	$(CC) $(TARGET) main.o -o $(EXEC) $(OPT)

test : $(TARGET) test.o
	$(CC) $(TARGET) test.o -o test $(OPT)

#option du makefile
clean:
	rm -rf *.o *.exe *.stackdump
	rm $(EXEC)

again:
	make clean
	make
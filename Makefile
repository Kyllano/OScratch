CC=gcc
OPT=-Wall -lm
EXEC=OScratch
TARGET=	bin/couche_1.o\
		bin/couche_2.o\
		bin/couche_3.o\
		bin/couche_4.o

all : $(EXEC)


#compile couches
bin/%.o : code/%.c
	$(CC) -o $@ -c $< $(OPT) 

#compile main
main.o : main.c
	$(CC) -o main.o -c main.c $(OPT)

#compile test
test.o : test.c
	$(CC) -o test.o -c test.c $(OPT)

#compile cmd_dump_inodes
# cmd_dump_inodes : code/cmd_dump_inodes.c
# 	$(CC) code/cmd_dump_inodes.c -o cmd_dump_inodes $(OPT)

#link main avec liste et element
$(EXEC): $(TARGET) bin/main.o
	$(CC) $(TARGET) bin/main.o -o $(EXEC) $(OPT)

test : $(TARGET) bin/test.o
	$(CC) $(TARGET) bin/test.o -o test $(OPT)

#option du makefile
clean:
	rm -rf *.o *.exe *.stackdump
	rm $(EXEC)

again:
	make clean
	make

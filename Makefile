CC=gcc
OPT=-Wall -lm
EXEC=OScratch
TARGET=	main.o\
		couche_1.o\
		couche_2.o\
		couche_3.o

all : $(EXEC)

#compile couche_1
couche_1.o: couche_1.c
	$(CC) -o couche_1.o -c couche_1.c $(OPT)

#compile couche_2
couche_2.o: couche_2.c
	$(CC) -o couche_2.o -c couche_2.c $(OPT)

#compile couche_3
couche_3.o: couche_3.c
	$(CC) -o couche_3.o -c couche_3.c $(OPT)

#compile main
main.o: main.c
	$(CC) -o main.o -c main.c $(OPT)

#compile cmd_dump_inodes
# cmd_dump_inodes : cmd_dump_inodes.c
# 	$(CC) cmd_dump_inodes.c -o cmd_dump_inodes $(OPT)

#link main avec liste et element
$(EXEC): $(TARGET)
	$(CC) $(TARGET) -o $(EXEC) -lm

#option du makefile
clean:
	rm -rf *.o *.exe *.stackdump
	rm $(EXEC)

again:
	make clean
	make
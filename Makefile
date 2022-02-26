CC=gcc
OPT=-Wall -lm
OBJDIR=bin
EXEC=OScratch
TARGET=	bin/timestamp.o\
		bin/couche_1.o\
		bin/couche_2.o\
		bin/couche_3.o\
		bin/couche_4.o

all : $(EXEC)


#compile couches
$(OBJDIR)/%.o : code/%.c
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
$(EXEC): $(TARGET) $(OBJDIR)/main.o
	$(CC) $(TARGET) $(OBJDIR)/main.o -o $(EXEC) $(OPT)

test : $(TARGET) $(OBJDIR)/test.o
	$(CC) $(TARGET) $(OBJDIR)/test.o -o test $(OPT)

#option du makefile
clean:
	rm -f $(OBJDIR)/*.o
	rm -rf $(EXEC)

again:
	make clean
	make

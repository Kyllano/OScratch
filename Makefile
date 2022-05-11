CC=gcc
OPT=-Wall -lm
OBJDIR=bin
SRCDIR=src
EXEC=OScratch
TARGET=	bin/sha256.o\
		bin/sha256_utils.o\
		bin/timestamp.o\
		bin/couche_1.o\
		bin/couche_2.o\
		bin/couche_3.o\
		bin/couche_4.o\
		bin/couche_5.o

all : $(EXEC)


#compile couches
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(OPT)

#compile main
program.o : program.c
	$(CC) -o program.o -c program.c $(OPT)

#compile test
test.o : test.c
	$(CC) -o test.o -c test.c $(OPT)

Installeur.o: Installeur.c
	$(CC) -o Installeur.o -c Installeur.c $(OPT)


#compile cmd_dump_inodes
# cmd_dump_inodes : src/cmd_dump_inodes.c
# 	$(CC) src/cmd_dump_inodes.c -o cmd_dump_inodes $(OPT)

#link main avec liste et element
$(EXEC): $(TARGET) $(OBJDIR)/program.o
	$(CC) $(TARGET) $(OBJDIR)/program.o -o $(EXEC) $(OPT)

debug: $(TARGET) $(OBJDIR)/program.o
	$(CC) $(TARGET) $(OBJDIR)/program.o -o $(EXEC) $(OPT) -g

test : $(TARGET) $(OBJDIR)/test.o
	$(CC) $(TARGET) $(OBJDIR)/test.o -o test $(OPT)

install: $(TARGET) $(OBJDIR)/Installeur.o
	$(CC) $(TARGET) $(OBJDIR)/Installeur.o -o install $(OPT)

#option du makefile
clean:
	rm -f $(OBJDIR)/*.o
	rm -rf $(EXEC)

again:
	make clean
	make

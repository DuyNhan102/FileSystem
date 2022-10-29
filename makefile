all: caseE

caseE: main.o fs.o
	$(CC) -o $@ $^


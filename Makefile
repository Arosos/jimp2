engine: main.o data.o rules.o solver.o
	$(CC) -o engine main.o data.o rules.o solver.o
clean:
	rm -f *.o engine

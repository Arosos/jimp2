engine: main.o data.o rules.o
	$(CC) -o engine main.o data.o rules.o
clean:
	rm -f *.o engine
